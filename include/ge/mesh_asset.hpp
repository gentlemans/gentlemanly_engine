#pragma once

#include "ge/asset.hpp"
#include "ge/mesh.hpp"
#include "ge/asset_manager.hpp"
#include "ge/json/json.h"

#include <memory>

/*
 * Asset Spec
 *
 * {
 *   "asset_type": "mesh",
 *   "obj_data": "/path/to/model.obj" # if this is omitted, then it defaults to
 * ./model.obj TODO:
 * add more file types
 * }
 *
 */

namespace ge
{
class mesh_asset : public asset
{
public:
	std::shared_ptr<mesh> data;

	mesh_asset(asset_manager& manager, const std::string& arg_name, const std::string& abs_filepath,
		const Json::Value& json_data);

	static std::string asset_name() { return "mesh"; }
};
}
