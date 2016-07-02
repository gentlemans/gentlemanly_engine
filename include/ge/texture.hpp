#ifndef GE_TEXTURE_HPP
#define GE_TEXTURE_HPP

#pragma once

#include <cstddef>
#include <cstdint>

#include <glm/glm.hpp>

namespace ge
{
class texture
{
public:
	// a null object
	texture(){};

	/// from uncompressed RGBA
	texture(const unsigned char* data, glm::uvec2 size);

	/// from compressed DXT -- no need for size, because YOU ARE GOING TO ALSO PASS THE HEADER!!!
	texture(const unsigned char* data);

	glm::uvec2 size = {};

	unsigned int texture_name = {};
};
}

#endif // GE_TEXTURE_HPP
