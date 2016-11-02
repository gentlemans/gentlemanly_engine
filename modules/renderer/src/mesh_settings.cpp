#include "ge/mesh_settings.hpp"

#include "ge/gl.hpp"

#include <vector>

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
	void operator()(int i) { glUniform1i(uniform_index, i); }
};

struct attr_applying_visitor : boost::static_visitor<size_t> {
	mesh const* m;
	shader const* shad;
	std::pair<const std::string, shader::attribute>* attr;

	template <typename T>
	size_t operator()(T atrtype)
	{
		auto attrLoc =
			glGetAttribLocation(shad->m_program_name, attr->second.attribute_name.c_str());
		glEnableVertexAttribArray(attrLoc);
		glBindBuffer(GL_ARRAY_BUFFER, m->additonal_vertex_data.find(attr->first)->second);
		glVertexAttribPointer(
			attrLoc, sizeof(atrtype) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(atrtype), nullptr);

		return attrLoc;
	}
};

void mesh_settings::render(const glm::mat3& mvp) const
{
	auto shader_ref = *m_material.m_shader;

	glUseProgram(shader_ref.m_program_name);
	// set parameters
	for (auto& param : shader_ref.m_parameters) {
		shader::parameter_type value;

		// check if it is in the material
		auto iter_in_mat = m_material.m_property_values.find(param.first);
		if (iter_in_mat != m_material.m_property_values.end()) {
			value = iter_in_mat->second;
		} else {
			value = param.second.value;
		}
		// set it
		parameter_setter_visitor v;
		v.uniform_index =
			glGetUniformLocation(shader_ref.m_program_name, param.second.glsl_name.c_str()) +
			param.second.offset;

		value.apply_visitor(v);
	}

	// set uniform in shader
	glUniformMatrix3fv(shader_ref.m_mvp_uniform_location, 1, GL_FALSE, &mvp[0][0]);

	glBindVertexArray(m_mesh->vertex_array);

	// TODO: not hardcoded
	auto locAttribLoc = glGetAttribLocation(shader_ref.m_program_name, "loc");
	glEnableVertexAttribArray(locAttribLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->vertex_buffer);
	glVertexAttribPointer(locAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

	std::vector<size_t> attribIDs;
	for (auto& attr : shader_ref.m_attributes) {
		
		// this means that not all the attributes that are required are present.
		assert(
			m_mesh->additonal_vertex_data.find(attr.first) != m_mesh->additonal_vertex_data.end());
		attr_applying_visitor visitor;
		visitor.m = m_mesh.get();
		visitor.attr = &attr;
		visitor.shad = &shader_ref;

		attribIDs.push_back(attr.second.type.apply_visitor(visitor));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->element_buffer);
	glDrawElements(GL_TRIANGLES, GLsizei(m_mesh->num_triangles * 3), GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(locAttribLoc);
	for (auto id : attribIDs) glDisableVertexAttribArray(id);
}
