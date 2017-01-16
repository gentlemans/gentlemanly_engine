#ifndef GE_MESH_SETTINGS_ASSET_HPP
#define GE_MESH_SETTINGS_ASSET_HPP

#pragma once

#include "ge/concept/asset.hpp"
#include "ge/material_asset.hpp"
#include "ge/mesh_asset.hpp"
#include "ge/mesh_settings.hpp"

namespace ge
{
/// Asset loader for mesh settings objects
/// [asset.json
/// spec](https://lbovet.github.io/docson/index.html#https://raw.githubusercontent.com/gentlemans/gentlemanly_engine/master/doc/json_spec/mesh_settings_asset.json)
struct mesh_settings_asset {
	/// Loads mesh_settings objects
	using loaded_type = mesh_settings;

	/// Asset loader function
	static std::shared_ptr<mesh_settings> load_asset(asset_manager& manager, const char* asset_name,
		const char* filepath, const nlohmann::json& json_data)
	{
		std::string mat = json_data["material"];
		std::string mesh = json_data["mesh"];

		return std::make_shared<mesh_settings>(manager.get_asset<mesh_asset>(mesh.c_str()),
			*manager.get_asset<material_asset>(mat.c_str()));
	}

	/// Require the assets to have "asset_type": "mesh_settings_asset"
	static const char* asset_type() { return "mesh_settings"; }
	// make sure it qualifies as an asset
	BOOST_CONCEPT_ASSERT((concept::Asset<mesh_settings_asset>));
};
}

#endif  // GE_MESH_SETTINGS_ASSET_HPP
