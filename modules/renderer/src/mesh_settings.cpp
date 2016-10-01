#include "ge/mesh_settings.hpp"

#include "ge/gl.hpp"

using namespace ge;

struct parameter_setter_visitor : boost::static_visitor<void> {
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

struct attr_applying_visitor : boost::static_visitor<void> {
	size_t attrib_id;
	mesh const* m;
	std::pair<const std::string, shader::attribute>* attr;

	template <typename T>
	void operator()(T atrtype)
	{
		glEnableVertexAttribArray(attrib_id);
		glBindBuffer(GL_ARRAY_BUFFER, m->additonal_vertex_data.find(attr->first)->second);
		glVertexAttribPointer(attr->second.attribute_id, sizeof(atrtype) / sizeof(float), GL_FLOAT,
			GL_FALSE, sizeof(atrtype), nullptr);
	}
};

void mesh_settings::render(const glm::mat3& mvp) const
{
	auto shader_ref = *m_material.m_shader;

	glUseProgram(shader_ref.program_name);
	// set parameters
	for (auto& param : shader_ref.parameters) {
		shader::parameter_type value;

		// check if it is in the material
		auto iter_in_mat = m_material.property_values.find(param.first);
		if (iter_in_mat != m_material.property_values.end()) {
			value = iter_in_mat->second;
		} else {
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

	glBindVertexArray(m_mesh->vertex_array);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->vertex_buffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

	size_t next_attribarray = 1;
	for (auto& attr : shader_ref.attributes) {
		assert(
			m_mesh->additonal_vertex_data.find(attr.first) != m_mesh->additonal_vertex_data.end());
		attr_applying_visitor visitor;
		visitor.attrib_id = next_attribarray++;
		visitor.m = m_mesh.get();
		visitor.attr = &attr;

		attr.second.type.apply_visitor(visitor);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->element_buffer);
	glDrawElements(GL_TRIANGLES, GLsizei(m_mesh->num_triangles * 3), GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(0);
	while (--next_attribarray) glDisableVertexAttribArray(GLuint(next_attribarray));
}
