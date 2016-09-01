#ifndef GE_SHADER_ASSET_HPP
#define GE_SHADER_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/concept/asset.hpp"
#include "ge/shader.hpp"
#include "ge/texture_asset.hpp"

#include "ge/json.hpp"
#include "ge/json_helper.hpp"

#include <string>

#include <boost/filesystem.hpp>
#include <boost/variant.hpp>

/* Asset Specification:
 *
 * asset.json
 *
 * {
 *   "asset_type": "shader",
 *   "vert_source": "/path/to/glsl/file, defaults to vert.glsl"
 *   "frag_source": "/path/to/glsl/file, defaults to frag.glsl"
 *   "vertex_attributes": [
 *     {
 *       "name": "name in the mesh",
 *       "glsl_id": "the attribute id in the shader (layout(locatio = n))"
 *       "type": "vec{x}|float",
 *     }
 *   ], (optional)
 *   "parameters": [
 *     {
 *       "type": "vec{x}|float|texture",
 *       "glsl_name": "name_of_uniform",
 *       "glsl_offset": "some int, 0 by default"
 *       "name": "the name that will be exposed to the interface"
 *       "default": "default value, use json for vectors ([x,y]) or asset path for textures",
 *       "description": "Brief description of what this prop does (optional)
 *     }
 *   ] (optional)
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
	using loaded_type = shader;

	static std::shared_ptr<shader> load_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data);

	static const char* asset_type() { return "shader"; }
};
BOOST_CONCEPT_ASSERT((concept::Asset<shader_asset>));
}

#endif  // GE_SHADER_ASSET_HPP
