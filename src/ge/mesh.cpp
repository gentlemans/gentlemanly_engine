#include "ge/gl.hpp"

#include "ge/mesh.hpp"

#include <algorithm>
#include <iostream>

#include <glm/glm.hpp>

namespace ge
{
mesh::mesh(const glm::vec2* points, const glm::vec2* texcoords, const size_t num_points,
	const glm::uvec3* indicies, const size_t num_indicies)
	: num_triangles{num_indicies}
{
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	// make buffers
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_points, points, GL_STATIC_DRAW);

	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_points, texcoords, GL_STATIC_DRAW);

	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::uvec3) * num_indicies, indicies, GL_STATIC_DRAW);
}

mesh::~mesh()
{
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &uv_buffer);
	glDeleteBuffers(1, &element_buffer);
}

}  // namespace ge
