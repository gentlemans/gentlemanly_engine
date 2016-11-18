#ifndef GE_SHADER_HPP
#define GE_SHADER_HPP

#pragma once

#include "ge/texture.hpp"

#include <cstdint>
#include <fstream>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include <boost/variant.hpp>

namespace ge
{
/// Represents a OpenGL program very directly, with not many extra features except easily
/// programmable parameters
class shader
{
public:
	/// The OpenGL program name
	uint32_t m_program_name = ~0;

	/// The types uses for parameters. Parameters can either be vec{2, 3, 4} or a texutre or a
	/// float.
	using parameter_type =
		boost::variant<int, float, glm::vec2, glm::vec3, glm::vec4, std::shared_ptr<texture>>;

	/// Vertex attributes can be a float, or vec{2, 3, 4}
	using attribute_type = boost::variant<int, float, glm::vec2, glm::vec3, glm::vec4>;

	/// The metadata that is stored for parameters
	struct parameter {
		/// The value of the parameter
		parameter_type value;

		/// The name in the shader for the parameter (uniform name)
		std::string glsl_name;

		/// A longer description for other developers for what the parameter does
		std::string description;

		/// The offset off of the glsl_name. This is usually just for arrays.
		uint32_t offset;
	};

	/// A constructor taking two streams as input
	/// \param vertex_stream The stream that holds the vertex shader data
	/// \param frag_stream The stream that holds the frag data
	shader(std::istream& vertex_stream, std::istream& frag_stream);

	/// A convenience constructor to allow for rvalue streams
	/// \param vertex_stream Stream with vertex data
	/// \param frag_stream Stream with frag data
	shader(std::istream&& vertex_stream, std::istream&& frag_stream)
		: shader{vertex_stream, frag_stream}
	{
	}

	/// A convenience constructor that just opens the files
	/// \param vertex_filename The name of a file with the vertex shader
	/// \param frag_filename The naem of a file with the fragment shader
	shader(const char* vertex_filename, const char* frag_filename)
		: shader{std::ifstream{vertex_filename}, std::ifstream{frag_filename}}
	{
	}
	
	shader(const shader&) = delete;
	shader(shader&&) = delete;
	
	shader& operator=(const shader&) = delete;
	shader& operator=(shader&&) = delete;

	/// The metadata that is stored for attributes
	struct attribute {
		/// The type of the attribute
		attribute_type type;

		/// The location assigned in GLSL for the attribute
		std::string attribute_name;
	};

	/// The default parameters, don't directly change this change it in the material
	/// If you change it here, you will be changing the defaults for _everyone using this texture_
	std::unordered_map<std::string, parameter> m_parameters;

	/// The attributes. don't directly change this unless you know what you are doing, it changes
	/// the default
	/// Instead of changing your specific instance
	std::unordered_map<std::string, attribute> m_attributes;

	/// The location of the mvp matrix uniform value
	int32_t m_mvp_uniform_location;

	/// The vertex location attribute name from glsl
	std::string m_vertex_location_attribute_name;

	/// Validity checking
	operator bool() { return m_program_name != ~0; }
};
}

#endif  // GE_SHADER_HPP
