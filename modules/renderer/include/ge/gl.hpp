#ifndef GE_GL_HPP
#define GE_GL_HPP

#pragma once

#if defined(__APPLE__) && !defined EMSCRIPTEN
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#elif defined(__linux__) && !defined EMSCRIPTEN
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#elif (defined(WIN32) || defined(_WIN32)) && !defined EMSCRIPTEN
#include <glad/glad.h>
#endif

#ifdef EMSCRIPTEN
#include <GLES3/gl2ext.h>
#include <GLES3/gl3.h>
#endif

#endif
