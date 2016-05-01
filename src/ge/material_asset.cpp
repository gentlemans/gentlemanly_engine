#include "ge/material_asset.hpp"

#include "ge/shader_asset.hpp"
#include "ge/texture_asset.hpp"

namespace ge
{
struct reassign_from_json_visitor : boost::static_visitor<shader::parameter_type>
{
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
		return asset_man.get_asset<texture_asset>(asset_path.c_str()).data;
	}
};

material_asset::material_asset(
	asset_manager& manager, const char* name, const char* filepath, const nlohmann::json& json_data)
{
	std::string asset_name = json_data["shader"];
	auto shader_ass = manager.get_asset<shader_asset>(asset_name.c_str());

	data = std::make_shared<material>(shader_ass.data);

	// load parameters
	auto iter = json_data.find("parameters");
	if (iter != json_data.end() && iter->is_array())
	{
		for (auto& parameter : *iter)
		{
			std::string name = parameter["name"];
			// get the type from the shader
			auto default_value = data->m_shader->parameters[name].value;

			reassign_from_json_visitor vis{parameter["value"], manager};

			try
			{
				data->property_values[name] = default_value.apply_visitor(vis);
			}
			catch (std::exception& e)
			{
				std::cerr << "ERROR THROWN: " << e.what() << std::endl;
			}
		}
	}
}
}
