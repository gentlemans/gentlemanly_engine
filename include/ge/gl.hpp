#pragma once

#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <OpenGL/gl3.h>
	#include <OpenGL/glu.h>
	#include <OpenGL/gl3ext.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#if defined(__linux__)
	#define GL_GLEXT_PROTOTYPES
	#include <GL/glext.h>
	#include <GL/glew.h>
#elif defined(WIN32) | defined(_WIN32)
	#include <windows.h>
	#include <gl/glew.h>
	#include "external/glext.h"
#endif
