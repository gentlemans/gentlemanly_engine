#include "ge/material_asset.hpp"

#include "ge/shader_asset.hpp"
#include "ge/texture_asset.hpp"

namespace ge
{
struct reassign_from_json_visitor : boost::static_visitor<shader::parameter_type> {
	reassign_from_json_visitor(const nlohmann::json& js, asset_manager& asset_man_arg)
		: json_obj{js}, asset_man{asset_man_arg}
	{
	}
	const nlohmann::json& json_obj;
	asset_manager& asset_man;

	shader::parameter_type operator()(float) { return (float)json_obj; }
	shader::parameter_type operator()(glm::vec2) { return glm::vec2{json_obj[0], json_obj[1]}; }
	shader::parameter_type operator()(glm::vec3)
	{
		return glm::vec3{json_obj[0], json_obj[1], json_obj[2]};
	}

	shader::parameter_type operator()(glm::vec4)
	{
		return glm::vec4{json_obj[0], json_obj[1], json_obj[2], json_obj[3]};
	}

	shader::parameter_type operator()(std::shared_ptr<texture>&)
	{
		std::string asset_path = json_obj;
		return asset_man.get_asset<texture_asset>(asset_path.c_str());
	}
};

material material_asset::load_asset(asset_manager& manager, const char* asset_name,
	const char* filepath, const nlohmann::json& json_data)
{
	std::string shader_asset_name = json_data["shader"];
	auto shader_ass = manager.get_asset<shader_asset>(shader_asset_name.c_str());

	auto ret = material(shader_ass);

	// load parameters
	auto parameter_iter = json_data.find("parameters");
	if (parameter_iter != json_data.end() && parameter_iter->is_object()) {
		for (auto pair_iter = parameter_iter->begin(); pair_iter != parameter_iter->end();
			 ++pair_iter) {
			std::string parameter_name = pair_iter.key();
			// get the type from the shader
			auto default_paramater_iter = ret.m_shader->parameters.find(parameter_name);
			if (default_paramater_iter == ret.m_shader->parameters.end()) {
				throw std::runtime_error("Could not find property: " + parameter_name +
										 " in shader while loading material asset: " + asset_name);
			}
			auto default_value = default_paramater_iter->second.value;

			reassign_from_json_visitor vis{pair_iter.value(), manager};

			try {
				ret.property_values[parameter_name] = default_value.apply_visitor(vis);
			} catch (std::exception& e) {
				std::cerr << "ERROR THROWN: " << e.what() << std::endl;
			}
		}
	}
	return ret;
}
}
