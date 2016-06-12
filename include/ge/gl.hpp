#pragma once

#if defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl3ext.h>
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#elif defined(WIN32) | defined(_WIN32)
#include <windows.h>
#include <gl/gl.h>
#include <gl/glew.h>
#include "external/glext.h"
#include "external/wglext.h"
#endif
