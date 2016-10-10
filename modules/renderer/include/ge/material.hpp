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
/// Settings overrider for materials
class material
{
public:
	/// The shader object that the material uses
	std::shared_ptr<const shader> m_shader;

	/// Default constructor--this will be an invalid material
	material() = default;
	/// Constructor from a shader
	material(const std::shared_ptr<const shader>& shader);

	/// Copy constructor
	material(const material&) = default;
	/// Move constructor
	material(material&&) = default;

	/// Destructor
	~material();

	/// Copy assignment
	material& operator=(const material&) = default;
	/// Move assignment
	material& operator=(material&&) = default;

	/// The overrided properties over the shader.
	std::unordered_map<std::string, shader::parameter_type> m_property_values;

	/// Validity check
	operator bool() const { return m_shader != nullptr; }
};
}

#endif  // GE_MATERIAL_HPP
