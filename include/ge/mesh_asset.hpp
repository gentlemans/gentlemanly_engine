#ifndef GE_MESH_ASSET_HPP
#define GE_MESH_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/json.hpp"
#include "ge/mesh.hpp"

#include <memory>

/*
 * Asset Spec
 *
 * {
 *   "asset_type": "mesh",
 *   "obj_data": "/path/to/model.obj, defauts to model.obj"
 *   "material": "/path/to/material/asset"
 * }
 *
 */

namespace ge
{
class mesh_asset
{
public:
	using loaded_type = mesh;

	static std::shared_ptr<mesh> load_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data);

	static const char* asset_type() { return "mesh"; }
};

BOOST_CONCEPT_ASSERT((concept::Asset<mesh_asset>));
}

#endif  // GE_MESH_ASSET_HPP
