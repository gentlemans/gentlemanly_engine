#include "ge/material_asset.hpp"

#include "ge/shader_asset.hpp"

namespace ge
{
material_asset::material_asset(asset_manager& manager, const std::string& name,
							   const std::string& filepath, const Json::Value& json_data)
	: asset(asset_name(), name, filepath)
{
	auto& shader_ass = manager.get_asset<shader_asset>(json_data["shader"].asCString());

	data = std::make_shared<material>(shader_ass.data);
}
}
