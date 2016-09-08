#include "ge/mesh_actor.hpp"
#include "ge/asset_manager.hpp"
#include "ge/material.hpp"
#include "ge/mesh.hpp"
#include "ge/mesh_asset.hpp"
#include "ge/shader.hpp"

namespace ge
{
void mesh_actor::initialize(const char* asset_path)
{
	initialize(m_runtime->m_asset_manager.get_asset<mesh_asset>(asset_path));
}

void mesh_actor::render(const glm::mat3& vp_mat)
{
	auto mvp = vp_mat * calculate_model_matrix();

	m_mesh->render(mvp);
}
}
