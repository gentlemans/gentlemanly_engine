#ifndef GE_MESH_HPP
#define GE_MESH_HPP

#pragma once

#include "ge/material.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include <boost/container/flat_map.hpp>

#include <glm/glm.hpp>

namespace ge
{
class material;

/// The low level representation of a mesh, just to store the data. Usually loaded from a
/// `ge::mesh_asset`
class mesh
{
public:
	/// Basic constructor
	/// \param points The location of the verticies
	/// \param num_points The size of the points array
	/// \param indicies The element data
	/// \param num_indicies The size of the indicies array
	mesh(const glm::vec2* points, const size_t num_points, const glm::uvec3* indicies,
		const size_t num_indicies);
	// no move or copy, pointer only
	mesh(const mesh&) = delete;
	mesh(mesh&&) = delete;
	mesh& operator=(const mesh&) = delete;
	mesh& operator=(mesh&&) = delete;

	/// Desctructor
	~mesh();

	/// Adds additional vertex data.
	/// \param name The name of the additional data, this should align with what the shader expects
	/// \param data The data for the attribute
	/// \param size The number of bytes in data
	void add_additional_data(const char* name, void* data, size_t size);

	// required data

	/// The OpenGL name for the vertex array
	unsigned vertex_array;

	/// The OpenGL name for the vertex position buffer
	unsigned vertex_buffer;

	/// The OpenGL name for the element buffer
	unsigned element_buffer;

	/// The amount of trianges in the mesh
	size_t num_triangles;

	/// additional data
	boost::container::flat_map<std::string, unsigned> additonal_vertex_data;
};
}

#endif  // GE_MESH_HPP
