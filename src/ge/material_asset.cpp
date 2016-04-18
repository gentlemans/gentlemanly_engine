#include "ge/material_asset.hpp"

#include "ge/shader_asset.hpp"

namespace ge
{
material_asset::material_asset(
	asset_manager& manager, const char* name, const char* filepath, const Json::Value& json_data)
{
	auto shader_ass = manager.get_asset<shader_asset>(json_data["shader"].asCString());

	data = std::make_shared<material>(shader_ass.data);
}
}
