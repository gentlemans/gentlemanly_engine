#ifndef GE_MESH_SETTINGS_ASSET_HPP
#define GE_MESH_SETTINGS_ASSET_HPP

#pragma once

#include "ge/material_asset.hpp"
#include "ge/mesh_asset.hpp"
#include "ge/mesh_settings.hpp"

namespace ge
{
/// Asset loader for mesh settings objects
///
/// ASSET SPECIFICATION
/// ```
/// {
///   "asset_type": "mesh_settings_asset",
///   "mesh": "/path/to/mesh_asset",
///   "material": "/path/to/material_asset"
/// }
/// ```
struct mesh_settings_asset {
	/// Loads mesh_settings objects
	using loaded_type = mesh_settings;

	/// Without cacheing
	using cached = std::false_type;

	/// Asset loader function
	static mesh_settings load_asset(asset_manager& manager, const char* asset_name,
		const char* filepath, const nlohmann::json& json_data)
	{
		std::string mat = json_data["material"];
		std::string mesh = json_data["mesh"];

		return mesh_settings{manager.get_asset<mesh_asset>(mesh.c_str()),
			manager.get_asset<material_asset>(mat.c_str())};
	}

	/// Require the assets to have "asset_type": "mesh_settings_asset"
	static const char* asset_type() { return "mesh_settings_asset"; }
};
}

#endif  // GE_MESH_SETTINGS_ASSET_HPP
