#include "ge/gl.hpp"

#include "ge/material.hpp"
#include "ge/mesh.hpp"
#include "ge/shader.hpp"

#include <algorithm>
#include <iostream>

#include <glm/glm.hpp>

namespace ge
{



mesh::mesh(const glm::vec2* points, const size_t num_points, const glm::uvec3* indicies,
	const size_t num_indicies)
	: num_triangles{num_indicies}
{
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	// make buffers
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_points, points, GL_STATIC_DRAW);

	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::uvec3) * num_indicies, indicies, GL_STATIC_DRAW);
}

void mesh::add_additional_data(const char* name, void* data, size_t size)
{
	unsigned gl_name;
	glGenBuffers(1, &gl_name);
	glBindBuffer(GL_ARRAY_BUFFER, gl_name);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	additonal_vertex_data.insert(
		decltype(additonal_vertex_data)::value_type{std::string(name), gl_name});
}



mesh::~mesh()
{
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &element_buffer);
}

}  // namespace ge
