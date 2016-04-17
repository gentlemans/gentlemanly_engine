#include "ge/shader.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

namespace ge
{
shader::shader(std::istream& vertex_stream, std::istream& frag_stream)
{
	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	// load source
	std::string vert_source(
		(std::istreambuf_iterator<char>(vertex_stream)), std::istreambuf_iterator<char>());
	std::string frag_source(
		(std::istreambuf_iterator<char>(frag_stream)), std::istreambuf_iterator<char>());

	GLint res = GL_NO_ERROR;
	int info_length;

	const char* vert_source_ptr = vert_source.c_str();
	glShaderSource(vert_shader, 1, &vert_source_ptr, nullptr);
	const char* frag_source_ptr = frag_source.c_str();
	glShaderSource(frag_shader, 1, &frag_source_ptr, nullptr);

	glCompileShader(vert_shader);
	glCompileShader(frag_shader);

	// check vertex shader
	glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &res);
	glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &info_length);
	if (info_length > 1)
	{
		std::string info_log(info_length + 1, '\n');
		glGetShaderInfoLog(vert_shader, info_length, nullptr, &info_log[0]);
		throw std::runtime_error("Failed to compile vertex shader: " + info_log);
	}

	// check fragment shader
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &res);
	glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &info_length);
	if (info_length > 1)
	{
		std::string info_log(info_length + 1, '\n');
		glGetShaderInfoLog(frag_shader, info_length, nullptr, &info_log[0]);
		throw std::runtime_error("Failed to compile fragment shader: " + info_log);
	}

	// link the shaders together
	program_name = glCreateProgram();

	glAttachShader(program_name, vert_shader);
	glAttachShader(program_name, frag_shader);
	glLinkProgram(program_name);

	// chcek the link
	glGetProgramiv(program_name, GL_LINK_STATUS, &res);
	glGetProgramiv(program_name, GL_INFO_LOG_LENGTH, &info_length);
	if (info_length > 1)
	{
		std::string info_log(info_length + 1, '\0');
		glGetProgramInfoLog(program_name, info_length, nullptr, &info_log[0]);
		throw std::runtime_error("Failed to link program: " + info_log);
	}

	// delete the shaders--they will stay alive until the program is deleted
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	mvp_uniform_location = glGetUniformLocation(program_name, "mvp_matrix");
}
}
