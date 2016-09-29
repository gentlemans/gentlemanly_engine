#ifndef GE_ORTHO2D_HPP
#define GE_ORTHO2D_HPP

#pragma once

#include <glm/glm.hpp>

// a quick ortho 2D
namespace glm
{
template <typename T>
GLM_FUNC_QUALIFIER tmat3x3<T, defaultp> ortho2d(T left, T right, T bottom, T top)
{
	tmat3x3<T, defaultp> Result(1);
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[2][0] = -(right + left) / (right - left);
	Result[2][1] = -(top + bottom) / (top - bottom);
	return Result;
}
}

#endif
