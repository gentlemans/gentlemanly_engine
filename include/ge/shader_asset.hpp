#pragma once

#include "ge/asset.hpp"
#include "ge/asset_manager.hpp"
#include "ge/shader.hpp"

#include <ge/json/json.h>

#include <string>

/* Asset Specification:
 *
 * asset.json
 *
 * {
 *   "asset_type": "shader",
 *   "vert_source": "/path/to/glsl/file" ** NOTE: if this is not set it defaults to vert.glsl in the
 * same directory
 *   "frag_source": "/path/to/glsl/file" ** Same here except to frag.glsl
 * }
 *
 */

namespace ge
{
class shader_asset : public asset
{
public:
	std::shared_ptr<shader> data;

	shader_asset(asset_manager& manager, const std::string& arg_name,
				 const std::string& abs_filepath, const Json::Value& json_data)
		: asset{asset_name(), arg_name, abs_filepath}
	{
		std::string vert_path =
			absolute_path + "/" + json_data.get("vert_source", "vert.glsl").asString();
		std::string frag_path =
			absolute_path + "/" + json_data.get("frag_source", "frag.glsl").asString();
		// just load the shader
		data = std::make_shared<shader>(vert_path.c_str(), frag_path.c_str());
	}

	static std::string asset_name() { return "shader"; }
};
}
