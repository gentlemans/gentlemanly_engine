#ifndef GE_MESH_SETTINGS_ASSET_HPP 
#define GE_MESH_SETTINGS_ASSET_HPP

#pragma once

#include "ge/mesh_settings.hpp"
#include "ge/mesh_asset.hpp"
#include "ge/material_asset.hpp"

/* ASSET SPECIFICATION
 * 
 * {
 *   "asset_type": "mesh_settings_asset",
 *   "mesh": "/path/to/mesh_asset",
 *   "material": "/path/to/material_asset"
 * }
 * 
 */

namespace ge {

struct mesh_settings_asset {
	using loaded_type = mesh_settings;
	using cached = std::false_type;
	
	static mesh_settings load_asset(asset_manager& manager, const char* asset_name, const char* filepath,
		const nlohmann::json& json_data) {
		
		std::string mat = json_data["material"];
		std::string mesh = json_data["mesh"];
		
		return mesh_settings{manager.get_asset<mesh_asset>(mesh.c_str()), manager.get_asset<material_asset>(mat.c_str())};
		
	}
	
	static const char* asset_type() { return "mesh_settings_asset"; }
	
};

}

#endif // GE_MESH_SETTINGS_ASSET_HPP
