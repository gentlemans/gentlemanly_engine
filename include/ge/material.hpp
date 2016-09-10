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

	material() = default;
	material(const std::shared_ptr<shader>& shader);
	
	material(const material&) = default;
	material(material&&) = default;
	
	material& operator=(const material&) = default;
	material& operator=(material&&) = default;

	std::unordered_map<std::string, shader::parameter_type> property_values;

	~material();
};
}

#endif  // GE_MATERIAL_HPP
