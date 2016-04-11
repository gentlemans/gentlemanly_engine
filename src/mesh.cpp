#include "ge/mesh.hpp"

#include <tiny_obj_loader.h>

#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

namespace ge {

mesh::mesh(std::istream& stream) 
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	tinyobj::MaterialFileReader reader({});
	tinyobj::LoadObj(shapes, materials, err, stream, reader, true);
	
	if(shapes.size() == 0) throw std::runtime_error("Error: No shapes in OBJ. Error: " + err);
	
	std::cout << "Loading mesh named: " << shapes[0].name;
	
	
	auto& mesh = shapes[0].mesh;
	
	num_triangles = mesh.indices.size() / 3;
	
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);
	
	// make buffers
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.positions.size(), mesh.positions.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.texcoords.size(), mesh.texcoords.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), mesh.positions.data(), GL_STATIC_DRAW);
	
	
}

mesh::~mesh()
{
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &uv_buffer);
	glDeleteBuffers(1, &element_buffer);
}


} // namespace ge
