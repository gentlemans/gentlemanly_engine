#ifndef GE_MATERIAL_HPP
#define GE_MATERIAL_HPP

#pragma once

#include "ge/log.hpp"
#include "ge/shader.hpp"

#include <memory>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include <boost/optional.hpp>

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

	void set_parameter(const char* key, shader::parameter_type value)
	{
		using namespace std::string_literals;

#ifndef _NDEBUG
		// check if the shader has this parameter
		if (m_shader->m_parameters.find(key) == m_shader->m_parameters.end()) {
			logger->warn(
				"Setting parameter in material \""s + key + "\" that doesn't exist in the shader");
		}
#endif
		m_property_values[key] = value;
	}

	template <typename T>
	boost::optional<T> get_parameter(const char* key) const
	{
		auto iter = m_property_values.find(key);
		if (iter == m_property_values.end()) {
			return {};
		}
		auto ptr = boost::get<T>(&iter->second);
		if (!ptr) return {};
		return *ptr;
	}

	/// Validity check
	operator bool() const { return m_shader != nullptr; }
	/// The overrided properties over the shader.
	std::unordered_map<std::string, shader::parameter_type> m_property_values;
};
}

#endif  // GE_MATERIAL_HPP
