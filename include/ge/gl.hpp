#pragma once

#ifdef __linux__
#	define GL_GLEXT_PROTOTYPES
#	include <GL/gl.h>
#	include <GL/glext.h>
#elif defined WIN32 | _WIN32
#	include <gl/glew.h>
#endif
