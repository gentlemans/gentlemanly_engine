#include "ge/model_actor.hpp"
#include "ge/material.hpp"
#include "ge/shader.hpp"
#include "ge/mesh.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

namespace ge
{
model_actor::model_actor(world& world, actor* parent, const std::shared_ptr<mesh>& arg_mesh,
	const std::shared_ptr<material>& mat)
	: actor(world, parent), mesh_for_model(arg_mesh), material_for_model(mat)
{
}

void model_actor::render(const glm::mat3& view_projection_matrix)
{
	auto mvp = view_projection_matrix * calculate_model_matrix();
	auto& shader_ref = *material_for_model->shader_for_material;
	auto& mesh_ref = *mesh_for_model;

	glUseProgram(shader_ref.program_name);

	// set uniform in shader
	glUniformMatrix3fv(shader_ref.mvp_uniform_location, 1, GL_FALSE, &mvp[0][0]);

	glBindVertexArray(mesh_ref.vertex_array);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_ref.vertex_buffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_ref.uv_buffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ref.element_buffer);
	glDrawElements(GL_TRIANGLES, mesh_ref.num_triangles * 3, GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
}
