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
class shader
{
public:
	uint32_t program_name;

	using parameter_type =
		boost::variant<float, glm::vec2, glm::vec3, glm::vec4, std::shared_ptr<texture>>;
	using attribute_type = boost::variant<float, glm::vec2, glm::vec3, glm::vec4>;

	struct parameter {
		parameter_type value;
		std::string glsl_name;
		std::string description;
		uint32_t offset;
	};

	shader(std::istream& vertex_stream, std::istream& frag_stream);
	shader(std::istream&& vertex_stream, std::istream&& frag_stream)
		: shader{vertex_stream, frag_stream}
	{
	}
	shader(const char* vertex_filename, const char* frag_filename)
		: shader{std::ifstream{vertex_filename}, std::ifstream{frag_filename}}
	{
	}

	struct attribute {
		attribute_type type;
		unsigned attribute_id;
	};

	std::unordered_map<std::string, parameter> parameters;
	std::unordered_map<std::string, attribute> attributes;

	int32_t mvp_uniform_location;
};
}
