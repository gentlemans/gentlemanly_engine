#ifndef GE_ASSET_MANAGER_HPP
#define GE_ASSET_MANAGER_HPP

#pragma once

#include "ge/concept/asset.hpp"
#include "ge/json.hpp"
#include "ge/subsystem.hpp"

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

namespace ge
{
class asset_manager
{
private:
	// not unordered because we need to traverse in order
	std::map<uint8_t, std::vector<std::string>> m_search_paths;

	// we don't know this type, but we will when it is asked for.
	std::unordered_map<std::string, std::weak_ptr<void>> cache;

	std::unordered_set<std::string> loaded_void_assets;

	// Meta-helper classes
	//////////////////////

	template <typename asset_type,
		bool = std::is_same<typename asset_type::cached, std::true_type>::value>
	struct is_already_in_cache_helper {
		static std::pair<std::shared_ptr<typename asset_type::loaded_type>, bool> exec(
			asset_manager& man, const char* name)
		{
			// check if it's in the cache
			auto iter = man.cache.find(name);
			if (iter != man.cache.end()) {
				if (!iter->second.expired()) {
					return {std::static_pointer_cast<typename asset_type::loaded_type>(
								iter->second.lock()),
						true};
				} else {
				}
			}
			return {nullptr, false};
		}
	};

	// if this evalutes, then the asset isn't cached
	template <typename asset_type>
	struct is_already_in_cache_helper<asset_type, false> {
		static std::pair<typename asset_type::loaded_type, bool> exec(asset_manager&, const char*)
		{
			return {typename asset_type::loaded_type{}, false};
		}
	};

	template <typename asset_type,
		bool = std::is_same<typename asset_type::cached, std::true_type>::value>
	struct cache_adder_helper {
		static void exec(asset_manager& man, const char* name,
			const std::shared_ptr<typename asset_type::loaded_type> ptr)
		{
			// add it to the cache
			auto weak = std::weak_ptr<void>(ptr);
			man.cache.insert({name, weak});
		}
	};

	// if this evalutes, then the asset isn't cached
	template <typename asset_type>
	struct cache_adder_helper<asset_type, false> {
		static void exec(asset_manager&, const char*, typename asset_type::loaded_type) {}
	};

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
	/// \param priority The priority of the path, the lower the priority the earlier it gets checked
	void add_asset_path(std::string path, uint8_t priority = 0)
	{
		if (!boost::filesystem::is_directory(path)) {
			throw std::runtime_error("Error opening asset path: " + path);
		}

		m_search_paths[priority].emplace_back(std::move(path));
	}

	/// Loads an asset from disk
	/// \param name The name of the asset, which is a folder inside an asset path
	/// \param extra_args Extra arguments to be passed to the loader
	/// \return The asset
	template <typename asset_type, typename... extra_args_types,
		typename = std::enable_if_t<!std::is_void<typename asset_type::loaded_type>::value>>
	// this ugly line gets the return type based on if the asset is cached or not. If it is cached,
	// then use a shared_ptr or else just use a raw value
	typename boost::mpl::if_<typename asset_type::cached,
		std::shared_ptr<typename asset_type::loaded_type>, typename asset_type::loaded_type>::type
	get_asset(const char* name, extra_args_types&&... extra_args)
	{
		using namespace std::string_literals;

		// make sure it's an asset
		BOOST_CONCEPT_ASSERT((concept::Asset<asset_type>));
		{
			// see if it's arleady in the cache
			auto pair = is_already_in_cache_helper<asset_type>::exec(*this, name);
			if (pair.second) return pair.first;
		}

		auto abs_path = resolve_asset_path(name);

		nlohmann::json root;
		std::ifstream asset_file(abs_path + "/asset.json");
		asset_file >> root;

		std::string asset_type_from_json = root["asset_type"];

		if (std::string(asset_type::asset_type()) != asset_type_from_json) {
			throw std::runtime_error("Asset type " + std::string(asset_type::asset_type()) +
									 " but the asset.json file in asset " + name +
									 " had asset type " + asset_type_from_json);
		}

		auto data = asset_type::load_asset(
			*this, name, abs_path.c_str(), root, std::forward<extra_args_types>(extra_args)...);

		cache_adder_helper<asset_type>::exec(*this, name, data);

		return data;
	}

	/// Loads a "void" asset from disk
	/// \param name The name of the asset, which is a folder inside an asset path
	/// \param extra_args Extra arguments to be passed to the loader
	template <typename asset_type, typename... extra_args_types,
		typename = std::enable_if_t<std::is_void<typename asset_type::loaded_type>::value>>
	void get_asset(const char* name, extra_args_types&&... extra_args)
	{
		using namespace std::string_literals;

		// make sure it's an asset
		BOOST_CONCEPT_ASSERT((concept::Asset<asset_type>));

		constexpr const bool is_cached =
			std::is_same<typename asset_type::cached, std::true_type>::value;

		// check if it's in the cache if the asset is cached
		if (is_cached) {
			auto iter = loaded_void_assets.find(name);
			if (iter != loaded_void_assets.end()) {
				return;
			}
		}

		auto abs_path = resolve_asset_path(name);

		nlohmann::json root;
		std::ifstream asset_file(abs_path + "/asset.json");
		asset_file >> root;

		std::string asset_type_from_json = root["asset_type"];

		if (std::string(asset_type::asset_type()) != asset_type_from_json) {
			throw std::runtime_error("Asset type " + std::string(asset_type::asset_type()) +
									 " but the asset.json file in asset " + name +
									 " had asset type " + asset_type_from_json);
		}

		asset_type::load_asset(
			*this, name, abs_path.c_str(), root, std::forward<extra_args_types>(extra_args)...);

		if (is_cached) loaded_void_assets.insert(name);
	}

	/// The runtime object that this manger belongs to
	runtime* m_runtime;

private:
	std::string resolve_asset_path(const char* name)
	{
		using namespace std::string_literals;

		std::string abs_path;
		// acquire absolute path
		for (auto& priority_and_paths : m_search_paths) {
			for (auto& path : priority_and_paths.second) {
				if (boost::filesystem::is_regular_file(path + "/" + name + "/asset.json")) {
					abs_path = path + "/" + name;
					break;
				}
			}
			if (!abs_path.empty()) break;
		}

		if (abs_path.empty()) {
			throw std::runtime_error(
				"Could not find asset named "s + name + " in any of the search paths");
		}

		if (!boost::filesystem::exists(abs_path + "/asset.json")) {
			throw std::runtime_error("Asset "s + name + " that was found in folder " + abs_path +
									 " does not have a asset.json file");
		}

		return abs_path;
	}
};
}

#endif  // GE_ASSET_MANAGER_HPP
