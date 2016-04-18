#pragma once

#include "ge/json/json.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>
#include <type_traits>

#include <boost/filesystem.hpp>

#include "ge/concept/asset.hpp"

namespace ge
{
class asset_manager
{
private:
	// not unordered because we need to traverse in order
	std::map<uint8_t, std::vector<std::string>> search_paths;

public:
	asset_manager() = default;
	asset_manager(const asset_manager&) = default;
	asset_manager(asset_manager&&) = default;

	asset_manager& operator=(const asset_manager&) = default;
	asset_manager& operator=(asset_manager&&) = default;

	// lower priority is earlier
	void add_asset_path(std::string path, uint8_t priority = 0);

	template <typename asset_type>
	asset_type get_asset(const char* name)
	{
		BOOST_CONCEPT_ASSERT((concept::Asset<asset_type>));

		using namespace std::string_literals;

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

		Json::Reader json_read;

		Json::Value root;
		std::ifstream asset_file(abs_path + "/asset.json");
		if (!json_read.parse(asset_file, root, false))
		{
			throw std::runtime_error("Could not parse file " + abs_path +
									 "/asset.json. Error message: " +
									 json_read.getFormattedErrorMessages());
		}

		std::string asset_type_from_json = root["asset_type"].asString();

		if (std::string(asset_type::asset_type()) != asset_type_from_json)
		{
			throw std::runtime_error("Asset type " + std::string(asset_type::asset_type()) +
									 " but the asset.json file in asset " + name +
									 " had asset type " + asset_type_from_json);
		}

		return asset_type(*this, name, abs_path.c_str(), root);
	}
};
}
