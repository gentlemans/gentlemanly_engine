#include "ge/model_system.hpp"
#include "ge/camera_component.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

namespace ge
{
struct parameter_setter_visitor : boost::static_visitor<void>
{
	int uniform_index;

	int bind_loc = 0;

	void operator()(float f) { glUniform1f(uniform_index, f); }
	void operator()(glm::vec2 vec) { glUniform2f(uniform_index, vec.x, vec.y); }
	void operator()(glm::vec3 vec) { glUniform3f(uniform_index, vec.x, vec.y, vec.z); }
	void operator()(glm::vec4 vec) { glUniform4f(uniform_index, vec.x, vec.y, vec.z, vec.w); }
	void operator()(const std::shared_ptr<texture>& tex)
	{
		glUniform1i(uniform_index, bind_loc);

		glActiveTexture(GL_TEXTURE0 + bind_loc);
		glBindTexture(GL_TEXTURE_2D, tex->texture_name);
	}
};

void model_system::update(
	entityx::EntityManager& em, entityx::EventManager& events, entityx::TimeDelta)
{
	auto camera_ent = *em.entities_with_components<camera_component>().begin();

	auto& camera_comp = *camera_ent.component<camera_component>().get();

	glm::mat3 projection =
		glm::ortho2d(-aspect * camera_comp.vertical_units, aspect * camera_comp.vertical_units,
			-camera_comp.vertical_units, camera_comp.vertical_units);
	glm::mat3 vp =
		projection * camera_ent.component<transform_component>()->calculate_model_matrix();

	for (auto ent : em.entities_with_components<model_component>())
	{
		assert(ent.has_component<model_component>());

		auto& model = *ent.component<model_component>().get();
		auto& material = *model.m_mesh->m_material;
		auto& shader = *material.m_shader;

		auto mvp = vp * ent.component<transform_component>()->calculate_model_matrix();

		mesh& mesh_ref = *model.m_mesh;

		glUseProgram(shader.program_name);
		// set parameters
		for (auto& param : shader.parameters)
		{
			shader::parameter_type value;

			// check if it is in the material
			auto iter_in_mat = material.property_values.find(param.first);
			if (iter_in_mat != material.property_values.end())
			{
				value = iter_in_mat->second;
			}
			else
			{
				value = param.second.value;
			}
			// set it
			parameter_setter_visitor v;
			v.uniform_index =
				glGetUniformLocation(shader.program_name, param.second.glsl_name.c_str()) +
				param.second.offset;

			value.apply_visitor(v);
		}

		// set uniform in shader
		glUniformMatrix3fv(shader.mvp_uniform_location, 1, GL_FALSE, &mvp[0][0]);

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
}
