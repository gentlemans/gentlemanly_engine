#include "ge/asset_manager.hpp"
#include "ge/asset.hpp"

#include <boost/filesystem.hpp>

#include <fstream>
#include <algorithm>

namespace ge
{
void asset_manager::add_asset_path(std::string path, uint8_t priority)
{
	search_paths[priority].emplace_back(std::move(path));
}

asset& asset_manager::get_asset_impl(const char* name)
{
	using namespace std::string_literals;
	
	// return early if we have already cached it
	auto iter = loaded_assets.find(name);
	if (iter != loaded_assets.end())
		{
			return *iter->second;
		}

	std::string abs_path;
	// acquire absolute path
	for (auto& priority_and_paths : search_paths)
		{
			for (auto& path : priority_and_paths.second)
				{
					if (boost::filesystem::is_directory(path + name))
						{
							abs_path = path + name;
							break;
						}
				}
			if (!abs_path.empty()) break;
		}
	if(abs_path.empty())
	{
		std::string search_paths_str = std::accumulate(search_paths.begin(), search_paths.end(), std::string{}, [](const std::string& a, decltype(search_paths)::value_type data)
		{
			return std::accumulate(data.second.begin(), data.second.end(), std::string{}, [](const std::string& str, const std::string& toAdd)
			{
				return str + ";" + toAdd;
			});
		});
		
		throw std::runtime_error("Could not find asset named "s + name + " in any of these search paths: " + search_paths_str);
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

	std::string asset_type = root["asset_type"].asString();
	auto new_asset = asset_types[asset_type](*this, name, abs_path, root);

	auto& ret = *new_asset;

	loaded_assets[name] = std::move(new_asset);

	return ret;
}

void asset_manager::register_asset_type(const std::string& asset_type_name,
										const asset_create_function& function_to_create_asset)
{
	asset_types[asset_type_name] = function_to_create_asset;
}
}
