#pragma once

#include "ge/concept/asset.hpp"
#include "ge/json.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include <boost/filesystem.hpp>

namespace ge
{
class asset_manager
{
private:
	// not unordered because we need to traverse in order
	std::map<uint8_t, std::vector<std::string>> search_paths;

	// we don't know this type, but we will when it is asked for.
	std::map<std::string, std::weak_ptr<void>> cache;

public:
	asset_manager() = default;
	asset_manager(const asset_manager&) = default;
	asset_manager(asset_manager&&) = default;

	asset_manager& operator=(const asset_manager&) = default;
	asset_manager& operator=(asset_manager&&) = default;

	/// Adds a search path to find assets
	/// \param path The path to add
	/// \param priority The priority of the path, the lower the priority the earlier it gets checked
	void add_asset_path(std::string path, uint8_t priority = 0);

	/// Loads an asset from disk
	/// \param name The name of the asset, which is a folder inside an asset path
	/// \param extra_args Extra arguments to be passed to the loader
	/// \return The asset
	template <typename asset_type, typename... extra_args_types>
	std::shared_ptr<typename asset_type::loaded_type> get_asset(
		const char* name, extra_args_types&&... extra_args)
	{
		using namespace std::string_literals;

		// make sure it's an asset
		BOOST_CONCEPT_ASSERT((concept::Asset<asset_type>));

		// check if it's in the cache
		{
			auto iter = cache.find(name);
			if (iter != cache.end())
			{
				if (!iter->second.expired())
					return std::static_pointer_cast<typename asset_type::loaded_type>(
						iter->second.lock());
			}
		}
		std::string abs_path;
		// acquire absolute path
		for (auto& priority_and_paths : search_paths)
		{
			for (auto& path : priority_and_paths.second)
			{
				if (boost::filesystem::is_regular_file(path + "/" + name + "/asset.json"))
				{
					abs_path = path + "/" + name;
					break;
				}
			}
			if (!abs_path.empty()) break;
		}

		if (abs_path.empty())
		{
			throw std::runtime_error(
				"Could not find asset named "s + name + " in any of the search paths");
		}

		if (!boost::filesystem::exists(abs_path + "/asset.json"))
		{
			throw std::runtime_error("Asset "s + name + " that was found in folder " + abs_path +
									 " does not have a asset.json file");
		}

		nlohmann::json root;
		std::ifstream asset_file(abs_path + "/asset.json");
		asset_file >> root;

		std::string asset_type_from_json = root["asset_type"];

		if (std::string(asset_type::asset_type()) != asset_type_from_json)
		{
			throw std::runtime_error("Asset type " + std::string(asset_type::asset_type()) +
									 " but the asset.json file in asset " + name +
									 " had asset type " + asset_type_from_json);
		}

		auto shared = asset_type::load_asset(
			*this, name, abs_path.c_str(), root, std::forward<extra_args_types>(extra_args)...);

		// add it to the cache
		auto weak = std::weak_ptr<void>(shared);
		cache.insert({name, weak});

		return shared;
	}
};
}
