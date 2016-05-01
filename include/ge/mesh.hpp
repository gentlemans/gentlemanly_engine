#pragma once

#include <cstdint>
#include <memory>

#include <glm/glm.hpp>

namespace ge
{
class material;
class mesh
{
public:
	std::shared_ptr<material> m_material;

	mesh(const glm::vec2* points, const glm::vec2* texcoords, const size_t num_points,
		const glm::uvec3* indicies, const size_t num_indicies);
	// no move or copy, pointer only
	mesh(const mesh&) = delete;
	mesh(mesh&&) = delete;
	mesh& operator=(const mesh&) = delete;
	mesh& operator=(mesh&&) = delete;

	~mesh();

	uint32_t vertex_array;
	uint32_t vertex_buffer;
	uint32_t uv_buffer;
	uint32_t element_buffer;

	size_t num_triangles;
};
}
