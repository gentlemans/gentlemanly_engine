#ifndef GE_TEXTURE_HPP
#define GE_TEXTURE_HPP

#pragma once

#include <cstddef>
#include <cstdint>

#include <glm/glm.hpp>

namespace ge
{
/// Represents a OpenGL texture object with very litte abstraction ontop
class texture
{
public:
	/// Initializes a null texutre object
	texture(){};

	/// Initialize from uncompressed 8-bit RGBA
	/// \param pixels The pixel data, the size of this array should be 4 * size.x * size.y
	/// \param size The size of the image
    /// \param name The name of the texture for debugging
    texture(const unsigned char* pixels, glm::uvec2 size, const char* name);

	/// Initialize from compressed DXT -- no need for size, because YOU ARE GOING TO ALSO PASS THE
	/// HEADER!!!
	/// \param data Raw DXT data
	texture(const unsigned char* data);

	/// The size of the shader
	glm::uvec2 size = {};

	/// The OpenGL name of the texture
	unsigned int texture_name = ~0;

	/// Validity test
	operator bool() const { return texture_name != ~0; }
};
}

#endif  // GE_TEXTURE_HPP
