#pragma once

#include "ge/mesh.hpp"
#include "ge/asset_manager.hpp"
#include "ge/json/json.h"

#include <memory>

/*
 * Asset Spec
 *
 * {
 *   "asset_type": "mesh",
 *   "obj_data": "/path/to/model.obj, defauts to model.obj"
 *   "default_material": "/path/to/material/asset"
 * }
 *
 */

namespace ge
{
class mesh_asset
{
public:
	std::shared_ptr<mesh> data;

	mesh_asset(asset_manager& manager, const std::string& arg_name, const std::string& abs_filepath,
		const Json::Value& json_data);

	static const char* asset_type() { return "mesh"; }
};
BOOST_CONCEPT_ASSERT((concept::Asset<mesh_asset>));
}
