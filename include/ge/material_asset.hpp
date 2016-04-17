#pragma once

#include "ge/asset.hpp"
#include "ge/material.hpp"
#include "ge/asset_manager.hpp"

#include "ge/json/json.h"

#include <memory>
#include <string>

/*
 * Asset Spec
 *
 * {
 *   "asset_type": "material",
 *   "shader": "/asset/name/for/shader",
 *   "textures": [
 *     {
 *       "name": "uniform name in glsl",
 *       "offset": "the offset of this texture if the uniform is an array, defaults to 0",
 *       "asset": "/asset/name/for/texture"
 *     }
 *   ],
 *   "parameters": [
 *     {
 *       "name_in_glsl": "vec{x} or float or mat{x}",
 *       "min": "minimum value. If vector, use {x, y} syntax, if matrix use {{x, y}, {x, y}} syntax. This is for GUI building.",
 *       "max": "maximum value. See minimum value for syntax.",
 *       "default": "default value, use above syntax"
 *     }
 *   ]
 * }
 *
 */

namespace ge
{
class material_asset : public asset
{
public:
	std::shared_ptr<material> data;

	material_asset(asset_manager& manager, const std::string& name, const std::string& filepath,
		const Json::Value& json_data);

	static std::string asset_name() { return "material"; }
};
}
