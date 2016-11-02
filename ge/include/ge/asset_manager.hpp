#ifndef GE_ASSET_MANAGER_HPP
#define GE_ASSET_MANAGER_HPP

#pragma once

#include "ge/concept/asset.hpp"
#include "ge/json.hpp"
#include "ge/log.hpp"
#include "ge/subsystem.hpp"

#include <spdlog/spdlog.h>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/mpl/if.hpp>

#include <boost/type_index.hpp>

namespace ge
{
/// Asset loader, and cacher.
class asset_manager
{
private:
	// not unordered because we need to traverse in order
	std::map<uint8_t, std::vector<std::string>> m_search_paths;

	// we don't know this type, but we will when it is asked for.
	std::unordered_map<std::string, std::shared_ptr<void>> cache;

	std::unordered_set<std::string> loaded_void_assets;

public:
	/// Construct a ge::asset_manager using the runtime
	/// This is almost always run by the runtime, it's very rare that a user would run this.
	asset_manager(runtime& run) : m_runtime{&run} {}
	// remove possible errors by deleting the copy and move constrctors
	asset_manager(const asset_manager&) = delete;
	asset_manager(asset_manager&&) = delete;

	asset_manager& operator=(const asset_manager&) = delete;
	asset_manager& operator=(asset_manager&&) = delete;

	/// Adds a search path to find assets
	/// \param path The path to add
	/// \param priority The priority of the path, 255 being the highest and 0 being the lowest
	/// priority
	void add_asset_path(std::string path, uint8_t priority = 0)
	{
		using namespace std::string_literals;

		if (!boost::filesystem::is_directory(path)) {
			logger->error("Error opening asset path: " + path +
						  ". Execution will continue, but assets might not load.");
			return;
		}
		logger->info("Added asset path \""s + path + "\"");

		m_search_paths[priority].emplace_back(std::move(path));
	}

	/// Loads an asset from disk
	/// \param name The name of the asset, which is a folder inside an asset path
	/// \return The asset
	template <typename asset_type,
		typename = std::enable_if_t<!std::is_void<typename asset_type::loaded_type>::value>>
	// this ugly line gets the return type based on if the asset is cached or not. If it is cached,
	// then use a shared_ptr or else just use a raw value
	std::shared_ptr<typename asset_type::loaded_type> get_asset(const char* name)
	{
		using namespace std::string_literals;

		// make sure it's an asset
		BOOST_CONCEPT_ASSERT((concept::Asset<asset_type>));

		// check if it's in the cache
		{
			auto iter = cache.find(name);
			if (iter != cache.end()) {
				return std::static_pointer_cast<typename asset_type::loaded_type>(iter->second);
			}
		}

		logger->debug("Trying to load asset that's not in cache: "s + name + " with type " +
					  boost::typeindex::type_id<asset_type>().pretty_name());

		auto abs_path = resolve_asset_path(name);

		nlohmann::json root;
		std::ifstream asset_file(abs_path + "/asset.json");
		asset_file >> root;

		std::string asset_type_from_json = root["asset_type"];

		if (std::string(asset_type::asset_type()) != asset_type_from_json) {
			logger->debug("Failed to load asset "s + name);

			logger->error("Asset type " + std::string(asset_type::asset_type()) +
						  " but the asset.json file in asset " + name + " had asset type " +
						  asset_type_from_json +
						  ". Asset will still be attempted to be loaded, but no promises.");
		}

		auto data = asset_type::load_asset(*this, name, abs_path.c_str(), root);

		// make sure it was actually loaded
		if (!data) {
			logger->error("Failed to load asset: "s + name + " with type " + asset_type_from_json +
						  ". Execution will continue, but will probably be broken");
			return data;
		}

		// add it to the cache
		cache.insert({name, data});

		logger->info("Successfully loaded asset \""s + name + "\" of type: " +
					 boost::typeindex::type_id<asset_type>().pretty_name());

		return data;
	}

	/// Loads a "void" asset from disk
	/// \param name The name of the asset, which is a folder inside an asset path
	template <typename asset_type,
		typename = std::enable_if_t<std::is_void<typename asset_type::loaded_type>::value>>
	void get_asset(const char* name)
	{
		using namespace std::string_literals;

		// make sure it's an asset
		BOOST_CONCEPT_ASSERT((concept::Asset<asset_type>));

		// check if it's in the cache
		auto iter = loaded_void_assets.find(name);
		if (iter != loaded_void_assets.end()) {
			return;
		}
		logger->debug("Trying to load void asset that's not in cache: "s + name + " with type " +
					  boost::typeindex::type_id<asset_type>().pretty_name());

		auto abs_path = resolve_asset_path(name);

		nlohmann::json root;
		std::ifstream asset_file(abs_path + "/asset.json");
		asset_file >> root;

		std::string asset_type_from_json = root["asset_type"];

		if (std::string(asset_type::asset_type()) != asset_type_from_json) {
			logger->debug("Failed to load asset "s + name);
			logger->error("Asset type " + std::string(asset_type::asset_type()) +
						  " but the asset.json file in asset " + name + " had asset type " +
						  asset_type_from_json +
						  ". Asset will still be attempted to be loaded, but no promises.");
		}

		asset_type::load_asset(*this, name, abs_path.c_str(), root);

		logger->info("Successfully loaded asset \""s + name + "\" of type: " +
					 boost::typeindex::type_id<asset_type>().pretty_name());

		loaded_void_assets.insert(name);
	}

	/// The runtime object that this manger belongs to
	runtime* m_runtime;

private:
	std::string resolve_asset_path(const char* name)
	{
		using namespace std::string_literals;

		std::string abs_path;
		// acquire absolute path; go backwards to make 255 the highest priority
		for (auto iter = m_search_paths.rbegin(); iter != m_search_paths.rend(); ++iter) {
			for (auto& path : iter->second) {
				if (boost::filesystem::is_regular_file(path + "/" + name + "/asset.json")) {
					abs_path = path + "/" + name;
					break;
				}
			}
			if (!abs_path.empty()) break;
		}

		if (abs_path.empty()) {
			logger->error("Could not find asset named "s + name + " in any of the search paths");
		}

		if (!boost::filesystem::exists(abs_path + "/asset.json")) {
			logger->error("Asset "s + name + " that was found in folder " + abs_path +
						  " does not have a asset.json file");
		}

		return abs_path;
	}
};
}

#endif  // GE_ASSET_MANAGER_HPP
