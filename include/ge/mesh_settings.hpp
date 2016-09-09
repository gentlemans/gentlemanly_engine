#ifndef GE_MESH_SETTINGS_HPP
#define GE_MESH_SETTINGS_HPP

#pragma once

#include "ge/mesh.hpp"
#include "ge/material.hpp"

namespace ge {

struct mesh_settings {
	
	mesh_settings(std::shared_ptr<mesh> arg_mesh, material arg_mat) : m_mesh{std::move(arg_mesh)}, m_material{std::move(arg_mat)}
		{}
	
	std::shared_ptr<mesh> m_mesh;
	material m_material;
	
	void render(const glm::mat3& mvp) const;
};

}

#endif // GE_MESH_SETTINGS_HPP
