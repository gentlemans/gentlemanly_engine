#ifndef GE_MATERIAL_HPP
#define GE_MATERIAL_HPP

#pragma once

#include "ge/shader.hpp"

#include <memory>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace ge
{
class material
{
public:
	std::shared_ptr<shader> m_shader;

	material(const std::shared_ptr<shader>& shader);

	std::unordered_map<std::string, shader::parameter_type> property_values;

	~material();
};
}

#endif // GE_MATERIAL_HPP
