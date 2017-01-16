#ifndef GE_MESH_SETTINGS_HPP
#define GE_MESH_SETTINGS_HPP

#pragma once

#include "ge/material.hpp"
#include "ge/mesh.hpp"

namespace ge
{
/// Represents settings for a mesh, including the mesh to use and material
struct mesh_settings {
	/// Constructor.
	/// \param arg_mesh The mesh to use
	/// \param arg_mat The material to copy from, the mesh_settings will have it's own copy
	mesh_settings(std::shared_ptr<mesh> arg_mesh, material arg_mat)
		: m_mesh{std::move(arg_mesh)}, m_material{std::move(arg_mat)}
	{
	}

	/// Default constructor. This will result in an invalid `mesh_settings` object
	mesh_settings() = default;

	/// Copy constructor
	mesh_settings(const mesh_settings&) = default;

	/// Move constructor
	mesh_settings(mesh_settings&&) = default;

	/// Copy assignment
	mesh_settings& operator=(const mesh_settings&) = default;

	/// Move assignment
	mesh_settings& operator=(mesh_settings&&) = default;

	/// The mesh
	std::shared_ptr<mesh> m_mesh;

	/// The material
	material m_material;

	/// Helper function to render this mesh at a certain position
	void render(const glm::mat3& mvp) const;
};
}

#endif  // GE_MESH_SETTINGS_HPP
