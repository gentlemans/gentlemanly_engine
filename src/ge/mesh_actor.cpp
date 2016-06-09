#include "ge/mesh_actor.hpp"
#include "ge/material.hpp"
#include "ge/mesh.hpp"
#include "ge/shader.hpp"

namespace ge
{
void mesh_actor::render(const glm::mat3& vp_mat)
{
	auto mvp = vp_mat * calculate_model_matrix();

	m_mesh->render(mvp);
}
}
