#include "ge/model_system.hpp"
#include "ge/camera_component.hpp"



#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>


namespace ge {
	
	void model_system::render_all(const anax::Entity& camera, float aspect)
	{

		auto& camera_comp = camera.getComponent<camera_component>();
		
		glm::mat3 projection = glm::ortho2d(-aspect * camera_comp.vertical_units,
			aspect * camera_comp.vertical_units, -camera_comp.vertical_units, camera_comp.vertical_units);
		glm::mat3 vp = projection; // TODO:  * camera_comp.calculate_model_matrix();
		
		
		for(auto& ent : entities)
		{
			
			assert(ent.hasComponent<model_component>());
			
			auto& model = ent.getComponent<model_component>();
			
			auto mvp = vp ; // TODO: * calculate_model_matrix();
			shader& shader_ref = *model.m_material->m_shader;
			mesh& mesh_ref = *model.m_mesh;

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
	
}

