#include "ge/texture.hpp"
#include "ge/gl.hpp"

#include <cassert>
#include <cstdio>

#include <stdexcept>

namespace ge
{
texture::texture(const unsigned char* pixels, glm::uvec2 arg_size) : size{arg_size}
{
	// just load straight up
	glGenTextures(1, &texture_name);
	glBindTexture(GL_TEXTURE_2D, texture_name);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

texture::texture::texture(const unsigned char* data)
{
	// load DXT texture
	// this code is from
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/#using-the-compressed-texture

	const unsigned char* header = data;

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	size = {width, height};

	const unsigned char* buffer = data + 124;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	/* close the file pointer */
	constexpr const unsigned FOURCC_DXT1 = 0x31545844;  // Equivalent to "DXT1" in ASCII
	constexpr const unsigned FOURCC_DXT3 = 0x33545844;  // Equivalent to "DXT3" in ASCII
	constexpr const unsigned FOURCC_DXT5 = 0x35545844;  // Equivalent to "DXT5" in ASCII

	//unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC) {
	case FOURCC_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
	case FOURCC_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
	case FOURCC_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
	default: throw std::runtime_error("Unrecognized DXT format");
	}

	// Create one OpenGL texture
	glGenTextures(1, &texture_name);

	// "Bind" the newly created texture : all future texture functions will modify this
	// texture
	glBindTexture(GL_TEXTURE_2D, texture_name);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) {
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		glCompressedTexImage2D(
			GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}
}
