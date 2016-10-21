#include "ge/shader_asset.hpp"

namespace ge
{
std::shared_ptr<shader> shader_asset::load_asset(asset_manager& manager,
	const std::string& arg_name, const std::string& abs_filepath, const nlohmann::json& json_data)
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
	auto ret = std::make_shared<shader>(vert_path.c_str(), frag_path.c_str());

	// load in the parameters
	auto param_iter = json_data.find("parameters");
	if (param_iter != json_data.end()) {
		auto parameters = *param_iter;
		if (parameters.is_array()) {
			for (auto& parameter : parameters) {
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
				if (type == "int") {
					param_data = (int)parameter["default"];
				} else if (type == "float") {
					param_data = (float)parameter["default"];
				} else if (type == "vec2") {
					glm::vec2 vector = {parameter["default"][0], parameter["default"][1]};
					param_data = vector;
				} else if (type == "vec3") {
					glm::vec3 vector = {
						parameter["default"][0], parameter["default"][1], parameter["default"][2]};
					param_data = vector;
				} else if (type == "vec4") {
					glm::vec4 vector = {parameter["default"][0], parameter["default"][1],
						parameter["default"][2], parameter["default"][3]};
					param_data = vector;
				} else if (type == "texture") {
					param_data = manager.get_asset<texture_asset>(
						parameter["default"].get<std::string>().c_str());
				}

				ret->m_parameters[name] = {param_data, glsl_name, description, offset};
			}
		}
	}

	// load in vertex_attributes
	auto attr_iter = json_data.find("vertex_attributes");
	if (attr_iter != json_data.end()) {
		auto vertex_attributes = *attr_iter;
		if (vertex_attributes.is_array()) {
			for (auto& attrib : vertex_attributes) {
				assert(attrib.is_object());

				// find out type
				std::string type = attrib["type"];
				auto attr_type = shader::attribute_type{};
				if (type == "int") {
					attr_type = int{};
				} else if (type == "float") {
					attr_type = float{};
				} else if (type == "vec2") {
					attr_type = glm::vec2{};
				} else if (type == "vec3") {
					attr_type = glm::vec3{};
				} else if (type == "vec4") {
					attr_type = glm::vec4{};
				}
				std::string glsl_name = attrib["glsl_name"];
				std::string attr_name = attrib["name"];
				ret->m_attributes.insert(std::pair<std::string, shader::attribute>{
					attr_name, shader::attribute{attr_type, glsl_name}});
			}
		}
	}
	return ret;
}
}
