#pragma once

#include "ge/asset.hpp"

#include <ge/json/json.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>
#include <type_traits>

namespace ge
{
class asset_manager
{
public:
	using asset_create_function =
		std::function<std::unique_ptr<asset>(asset_manager& manager, const std::string& asset_name,
			const std::string& asset_directory, const Json::Value& json_data)>;

private:
	// not unordered because we need to traverse in order
	std::map<uint8_t, std::vector<std::string>> search_paths;

	std::unordered_map<std::string, std::unique_ptr<asset>> loaded_assets;

	std::unordered_map<std::string, asset_create_function> asset_types;

	asset& get_asset_impl(const char* name);

public:
	asset_manager() = default;
	asset_manager(const asset_manager&) = default;
	asset_manager(asset_manager&&) = default;

	asset_manager& operator=(const asset_manager&) = default;
	asset_manager& operator=(asset_manager&&) = default;

	// lower priority is earlier
	void add_asset_path(std::string path, uint8_t priority = 0);

	template <typename asset_type = asset,
		typename = std::enable_if_t<std::is_base_of<asset, asset_type>::value>>
	asset_type& get_asset(const char* name)
	{
		return static_cast<asset_type&>(get_asset_impl(name));
	}

	void register_asset_type(
		const std::string& asset_type_name, const asset_create_function& function_to_create_asset);

	template <typename asset_type,
		typename = std::enable_if_t<std::is_base_of<asset, asset_type>::value>>
	void register_asset_type()
	{
		register_asset_type(asset_type::asset_name(),
			[](asset_manager& manager, const std::string& name, const std::string& abs_path,
								const Json::Value& value)
			{
				return std::make_unique<asset_type>(manager, name, abs_path, value);
			});
	}
};
}
