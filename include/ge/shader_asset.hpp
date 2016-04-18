#pragma once

#include "ge/asset_manager.hpp"
#include "ge/shader.hpp"
#include "ge/concept/asset.hpp"

#include <ge/json/json.h>

#include <string>

#include <boost/variant.hpp>
#include <boost/filesystem.hpp>

/* Asset Specification:
 *
 * asset.json
 *
 * {
 *   "asset_type": "shader",
 *   "vert_source": "/path/to/glsl/file, defaults to vert.glsl"
 *   "frag_source": "/path/to/glsl/file, defaults to frag.glsl"
 *   "textures": [
 *     {
 *       "name": "uniform name in glsl",
 *       "offset": "the offset of this texture if the uniform is an array, defaults to 0",
 *       "default": "/asset/name/for/texture"
 *     }
 *   ],
 *   "parameters": [
 *     {
 *       "name_in_glsl": "vec{x} or float",
 *       "min": "minimum value. If vector, use {x, y} syntax. This is for GUI building.",
 *       "max": "maximum value. See minimum value for syntax.",
 *       "default": "default value, use above syntax"
 *     }
 *   ]
 * }
 *
 */

namespace ge
{
/**
 *
 * A shader_asset loads a shader, and exposes properties to this shader, to be set in a material.
 *
 */
class shader_asset
{
public:
	std::shared_ptr<shader> data;

	shader_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const Json::Value& json_data)
	{
		std::string vert_path =
			boost::filesystem::absolute(
				json_data.get("vert_source", "vert.glsl").asString(), abs_filepath)
				.string();
		std::string frag_path =
			boost::filesystem::absolute(
				json_data.get("frag_source", "frag.glsl").asString(), abs_filepath)
				.string();

		// just load the shader
		data = std::make_shared<shader>(vert_path.c_str(), frag_path.c_str());
	}

	static const char* asset_type() { return "shader"; }
};
BOOST_CONCEPT_ASSERT((concept::Asset<shader_asset>));
}
