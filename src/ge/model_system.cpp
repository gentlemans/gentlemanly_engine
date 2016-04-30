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

	void operator()(float f) { glUniform1f(uniform_index, f); }
	void operator()(glm::vec2 vec) { glUniform2f(uniform_index, vec.x, vec.y); }
	void operator()(glm::vec3 vec) { glUniform3f(uniform_index, vec.x, vec.y, vec.z); }
	void operator()(glm::vec4 vec) { glUniform4f(uniform_index, vec.x, vec.y, vec.z, vec.w); }
};

void model_system::render_all(const anax::Entity& camera, float aspect)
{
	auto& camera_comp = camera.getComponent<camera_component>();

	glm::mat3 projection =
		glm::ortho2d(-aspect * camera_comp.vertical_units, aspect * camera_comp.vertical_units,
			-camera_comp.vertical_units, camera_comp.vertical_units);
	glm::mat3 vp = projection;  // TODO:  * camera_comp.calculate_model_matrix();

	for (auto& ent : entities)
	{
		assert(ent.hasComponent<model_component>());

		auto& model = ent.getComponent<model_component>();

		auto mvp = vp;  // TODO: * calculate_model_matrix();
		shader& shader_ref = *model.m_material->m_shader;
		mesh& mesh_ref = *model.m_mesh;

		material& mat_ref = *model.m_material;

		glUseProgram(shader_ref.program_name);
		// set parameters
		for (auto& param : shader_ref.parameters)
		{
			shader::parameter_type value;

			// check if it is in the material
			auto iter_in_mat = mat_ref.property_values.find(param.first);
			if (iter_in_mat != mat_ref.property_values.end())
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
				glGetUniformLocation(shader_ref.program_name, param.second.glsl_name.c_str()) +
				param.second.offset;

			value.apply_visitor(v);
		}

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
}
