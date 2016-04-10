#include "ge/shader.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

namespace ge {

shader::shader(std::istream& vertex_stream, std::istream& frag_stream)
{
	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// load source
	std::string vert_source((std::istreambuf_iterator<char>(vertex_stream)), std::istreambuf_iterator<char>());
	std::string frag_source((std::istreambuf_iterator<char>(frag_stream)), std::istreambuf_iterator<char>());
	
	GLint res = GL_FALSE;
	
	
}

}
