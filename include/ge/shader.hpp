#pragma once

#include <fstream>
#include <cstdint>

namespace ge {

class shader 
{
public:
	uint32_t program_name;
	
	shader(std::istream& vertex_stream, std::istream& frag_stream);
	shader(std::istream&& vertex_stream, std::istream&& frag_stream) : shader{vertex_stream, frag_stream} {}
	shader(const char* vertex_filename, const char* frag_filename) 
		: shader{std::ifstream{vertex_filename}, std::ifstream{frag_filename}} {}
	
	int32_t mvp_uniform_location;
};

}
