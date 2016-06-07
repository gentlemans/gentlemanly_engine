#include "ge/gl.hpp"

#include "ge/mesh.hpp"
#include "ge/material.hpp"
#include "ge/shader.hpp"

#include <algorithm>
#include <iostream>

#include <glm/glm.hpp>


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

struct attr_applying_visitor : boost::static_visitor<void>
{
	unsigned attrib_id;
	mesh const* m;
	std::pair<const std::string, shader::attribute>* attr;
	
	
	template<typename T>
	void operator()(T atrtype) {
			glEnableVertexAttribArray(attrib_id);
			glBindBuffer(GL_ARRAY_BUFFER, m->additonal_vertex_data.find(attr->first)->second);
			glVertexAttribPointer(attr->second.attribute_id, sizeof(atrtype) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(atrtype), nullptr);
		}
	
};


	
mesh::mesh(const glm::vec2* points, const size_t num_points,
	const glm::uvec3* indicies, const size_t num_indicies)
	: num_triangles{num_indicies}
{
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	// make buffers
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_points, points, GL_STATIC_DRAW);

	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::uvec3) * num_indicies, indicies, GL_STATIC_DRAW);
}

void mesh::add_additonal_data(const char* name, void* data, size_t size) {
	
	unsigned gl_name;
	glGenBuffers(1, &gl_name);
	glBindBuffer(GL_ARRAY_BUFFER, gl_name);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	
	additonal_vertex_data.insert(decltype(additonal_vertex_data)::value_type{std::string(name), gl_name});
}

void mesh::render(const glm::mat3& mvp) const {
	
	auto material_ref = *m_material;
	auto shader_ref = *material_ref.m_shader;
	
	glUseProgram(shader_ref.program_name);
	// set parameters
	for (auto& param : shader_ref.parameters)
	{
		shader::parameter_type value;

		// check if it is in the material
		auto iter_in_mat = material_ref.property_values.find(param.first);
		if (iter_in_mat != material_ref.property_values.end())
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

	glBindVertexArray(vertex_array);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

	size_t next_attribarray = 1;
	for(auto& attr : shader_ref.attributes) {
		assert(additonal_vertex_data.find(attr.first) != additonal_vertex_data.end());
		attr_applying_visitor visitor;
		visitor.attrib_id = next_attribarray++;
		visitor.m = this;
		visitor.attr = &attr;
		
		attr.second.type.apply_visitor(visitor);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glDrawElements(GL_TRIANGLES, num_triangles * 3, GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(0);
	while(--next_attribarray) glDisableVertexAttribArray(next_attribarray);
}

mesh::~mesh()
{
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &element_buffer);
}

}  // namespace ge
