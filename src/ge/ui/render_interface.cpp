#include "ge/ui/render_interface.hpp"
#include "ge/gl.hpp"
#include "ge/mesh.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Rocket/Core/FileInterface.h>
#include <Rocket/Core.h>

namespace ge
{
namespace ui
{
render_interface::render_interface()
{
}

// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void render_interface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices,
	int* indices, int num_indices, const Rocket::Core::TextureHandle texture,
	const Rocket::Core::Vector2f& translation)
{
	glPushMatrix();
	glTranslatef(translation.x, translation.y, 0);

	glVertexPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex), &vertices[0].position);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Rocket::Core::Vertex), &vertices[0].colour);

	if (!texture)
	{
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (GLuint)texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex), &vertices[0].tex_coord);
	}

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

	glPopMatrix();
}


Rocket::Core::CompiledGeometryHandle render_interface::CompileGeometry(
	Rocket::Core::Vertex* vertices,
	int num_vertices, int* indices,
	int num_indices,
	const Rocket::Core::TextureHandle texture)
{
	// create a ge::mesh
	std::vector<glm::vec2> locs; locs.reserve(num_vertices);
	std::vector<glm::vec2> tex_coord; tex_coord.reserve(num_vertices);
	std::vector<glm::vec4> colors; colors.reserve(num_vertices);
	for(size_t id = 0; id < num_vertices; ++id) {
		locs.emplace_back(vertices[id].position.x, vertices[id].position.x);
		tex_coord.emplace_back(vertices[id].tex_coord.x, vertices[id].tex_coord.y);
		colors.emplace_back(vertices[id].colour.red, vertices[id].colour.green, vertices[id].colour.blue, vertices[id].colour.alpha);
	}
	
	auto mes = new mesh(locs.data(), num_vertices, reinterpret_cast<glm::uvec3*>(indices), num_indices);
	
	return (intptr_t)mes;
	
}

// Called by Rocket when it wants to render application-compiled geometry.
void render_interface::RenderCompiledGeometry(
	Rocket::Core::CompiledGeometryHandle geometry,
	const Rocket::Core::Vector2f& translation)
{
	glm::mat3 mvp = glm::translate(glm::mat3{}, {translation.x, translation.y});
	
	
}

// Called by Rocket when it wants to release application-compiled geometry.
void render_interface::ReleaseCompiledGeometry(
	Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED_PARAMETER(geometry))
{
	ROCKET_UNUSED(geometry);
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.
void render_interface::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

// Called by Rocket when it wants to change the scissor region.
void render_interface::SetScissorRegion(int x, int y, int width, int height)
{
	//glScissor(x, m_height - (y + height), width, height);
}

// Set to byte packing, or the compiler will expand our struct, which means it won't read correctly
// from file
#pragma pack(1)
struct TGAHeader
{
	char idLength;
	char colourMapType;
	char dataType;
	short int colourMapOrigin;
	short int colourMapLength;
	char colourMapDepth;
	short int xOrigin;
	short int yOrigin;
	short int width;
	short int height;
	char bitsPerPixel;
	char imageDescriptor;
};
// Restore packing
#pragma pack()

// Called by Rocket when a texture is required by the library.
bool render_interface::LoadTexture(Rocket::Core::TextureHandle& texture_handle,
	Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (!file_handle)
	{
		return false;
	}

	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);

	ROCKET_ASSERTMSG(buffer_size > sizeof(TGAHeader),
		"Texture file size is smaller than TGAHeader, file must be corrupt or otherwise invalid");
	if (buffer_size <= sizeof(TGAHeader))
	{
		file_interface->Close(file_handle);
		return false;
	}

	char* buffer = new char[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);

	TGAHeader header;
	memcpy(&header, buffer, sizeof(TGAHeader));

	int color_mode = header.bitsPerPixel / 8;
	int image_size = header.width * header.height * 4;  // We always make 32bit textures

	if (header.dataType != 2)
	{
		Rocket::Core::Log::Message(
			Rocket::Core::Log::LT_ERROR, "Only 24/32bit uncompressed TGAs are supported.");
		return false;
	}

	// Ensure we have at least 3 colors
	if (color_mode < 3)
	{
		Rocket::Core::Log::Message(
			Rocket::Core::Log::LT_ERROR, "Only 24 and 32bit textures are supported");
		return false;
	}

	const char* image_src = buffer + sizeof(TGAHeader);
	unsigned char* image_dest = new unsigned char[image_size];

	// Targa is BGR, swap to RGB and flip Y axis
	for (long y = 0; y < header.height; y++)
	{
		long read_index = y * header.width * color_mode;
		long write_index = ((header.imageDescriptor & 32) != 0)
							   ? read_index
							   : (header.height - y - 1) * header.width * color_mode;
		for (long x = 0; x < header.width; x++)
		{
			image_dest[write_index] = image_src[read_index + 2];
			image_dest[write_index + 1] = image_src[read_index + 1];
			image_dest[write_index + 2] = image_src[read_index];
			if (color_mode == 4)
				image_dest[write_index + 3] = image_src[read_index + 3];
			else
				image_dest[write_index + 3] = 255;

			write_index += 4;
			read_index += color_mode;
		}
	}

	texture_dimensions.x = header.width;
	texture_dimensions.y = header.height;

	bool success = GenerateTexture(texture_handle, image_dest, texture_dimensions);

	delete[] image_dest;
	delete[] buffer;

	return success;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of
// pixels.
bool render_interface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle,
	const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	GLuint texture_id = 0;
	glGenTextures(1, &texture_id);
	if (texture_id == 0)
	{
		printf("Failed to generate textures\n");
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, source_dimensions.x, source_dimensions.y, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, source);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	texture_handle = (Rocket::Core::TextureHandle)texture_id;

	return true;
}

// Called by Rocket when a loaded texture is no longer required.
void render_interface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	glDeleteTextures(1, (GLuint*)&texture_handle);
}
}
}
