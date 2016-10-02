#ifndef GE_MESH_ASSET_HPP
#define GE_MESH_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/json.hpp"
#include "ge/mesh.hpp"

#include <memory>

namespace ge
{
/// An asset for loading meshes
/// [asset.json specification](https://lbovet.github.io/docson/index.html#https://raw.githubusercontent.com/gentlemans/gentlemanly_engine/master/doc/json_spec/mesh_asset.json)
class mesh_asset
{
public:
	/// Loads meshes
	using loaded_type = mesh;

	/// With caching
	using cached = std::true_type;

	/// Asset loading function
	static std::shared_ptr<mesh> load_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data);

	/// Require the asset to have "asset_type": "mesh"
	static const char* asset_type() { return "mesh"; }
};

BOOST_CONCEPT_ASSERT((concept::Asset<mesh_asset>));
}

#endif  // GE_MESH_ASSET_HPP
