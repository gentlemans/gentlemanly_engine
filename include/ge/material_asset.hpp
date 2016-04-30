#pragma once

#include "ge/material.hpp"
#include "ge/asset_manager.hpp"

#include "ge/json.hpp"

#include <memory>
#include <string>
#include <vector>

/*
 * Asset Spec
 *
 * {
 *   "asset_type": "material",
 *   "shader": "/asset/name/for/shader",
 *   "parameters": [
 *     {
 *       "name": "the name from the shader",
 *       "value": "the value, use JSON arrays ([2.0, 2.1]) for vectors."
 *     }
 *   ]
 * }
 *
 */

namespace ge
{
class material_asset
{
public:
	std::shared_ptr<material> data;

	material_asset(asset_manager& manager, const char* name, const char* filepath,
		const nlohmann::json& json_data);

	static const char* asset_type() { return "material"; }
};

BOOST_CONCEPT_ASSERT((concept::Asset<material_asset>));
}
