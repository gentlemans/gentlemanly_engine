#pragma once

#include "ge/shader.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include <boost/container/flat_map.hpp>

#include <glm/glm.hpp>

namespace ge
{
class material;
class mesh
{
public:
	std::shared_ptr<material> m_material;

	mesh(const glm::vec2* points, const size_t num_points, const glm::uvec3* indicies,
		const size_t num_indicies);
	// no move or copy, pointer only
	mesh(const mesh&) = delete;
	mesh(mesh&&) = delete;
	mesh& operator=(const mesh&) = delete;
	mesh& operator=(mesh&&) = delete;

	~mesh();

	void add_additonal_data(const char* name, void* data, size_t size);

	void render(const glm::mat3& mvp) const;

	// required data
	unsigned vertex_array;
	unsigned vertex_buffer;

	unsigned element_buffer;
	size_t num_triangles;

	// additional data
	boost::container::flat_map<std::string, unsigned> additonal_vertex_data;
};
}
