#pragma once

#include "ge/asset_manager.hpp"
#include "ge/shader.hpp"
#include "ge/concept/asset.hpp"
#include "ge/texture_asset.hpp"

#include "ge/json.hpp"
#include "ge/json_helper.hpp"

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
	std::shared_ptr<shader> data;

	shader_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data)
	{
		using namespace std::string_literals;

		std::string vert_path =
			boost::filesystem::absolute(
				json_get_value_with_fallback(json_data, "vert_source"s, "vert.glsl"s), abs_filepath)
				.string();
		std::string frag_path =
			boost::filesystem::absolute(
				json_get_value_with_fallback(json_data, "frag_source"s, "frag.glsl"s), abs_filepath)
				.string();

		// just load the shader
		data = std::make_shared<shader>(vert_path.c_str(), frag_path.c_str());

		// load in the parameters
		nlohmann::json parameters = json_data["parameters"];
		if (parameters.is_array())
		{
			for (auto& parameter : parameters)
			{
				// required
				std::string type = parameter["type"];
				std::string glsl_name = parameter["glsl_name"];
				std::string name = parameter["name"];
				std::string description = parameter["description"];

				// optional
				uint32_t offset =
					parameter["offset"].is_number_integer() ? (uint32_t)parameter["offset"] : 0;

				shader::parameter_type param_data;

				// figure out type
				if (type == "float")
				{
					param_data = (float)parameter["default"];
				}
				else if (type == "vec2")
				{
					glm::vec2 vector = {parameter["default"][0], parameter["default"][1]};
					param_data = vector;
				}
				else if (type == "vec3")
				{
					glm::vec3 vector = {
						parameter["default"][0], parameter["default"][1], parameter["default"][2]};
					param_data = vector;
				}
				else if (type == "vec4")
				{
					glm::vec4 vector = {parameter["default"][0], parameter["default"][1],
						parameter["default"][2], parameter["default"][3]};
					param_data = vector;
				}
				else if (type == "texture")
				{
					
					param_data = manager.get_asset<texture_asset>(parameter["default"].get<std::string>().c_str()).data;
				}

				data->parameters[name] = {param_data, glsl_name, description, offset};
			}
		}
	}

	static const char* asset_type() { return "shader"; }
};
BOOST_CONCEPT_ASSERT((concept::Asset<shader_asset>));
}
