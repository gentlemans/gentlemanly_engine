#pragma once

#include <cstdint>
#include <fstream>

namespace ge {

class mesh 
{
	mesh(std::istream& stream);
	mesh(std::istream&& stream) : mesh(stream){}
	mesh(const char* filename) : mesh(std::ifstream{filename}){}
	
	// no move or copy, pointer only
	mesh(const mesh&) = delete;
	mesh(mesh&&) = delete;
	mesh& operator=(const mesh&) = delete;
	mesh& operator=(mesh&&) = delete;
	
	~mesh();
	
private:
	
	uint32_t vertex_buffer;
	uint32_t uv_buffer;
	uint32_t element_buffer;
};

}
