#include "ge/ui/render_interface.hpp"
#include "ge/gl.hpp"
#include "ge/material.hpp"
#include "ge/mesh.hpp"
#include "ge/mesh_settings.hpp"
#include "ge/ortho2d.hpp"
#include "ge/texture_asset.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Rocket/Core.h>
#include <Rocket/Core/FileInterface.h>

namespace ge
{
namespace ui
{
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

	if (!texture) {
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} else {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (GLuint)texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex), &vertices[0].tex_coord);
	}

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

	glPopMatrix();
}

Rocket::Core::CompiledGeometryHandle render_interface::CompileGeometry(
	Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices,
	const Rocket::Core::TextureHandle texturehandle)
{
	// create a ge::mesh
	std::vector<glm::vec2> locs;
	locs.reserve(num_vertices);
	std::vector<glm::vec2> tex_coord;
	tex_coord.reserve(num_vertices);
	std::vector<glm::vec4> colors;
	colors.reserve(num_vertices);

	// reconstruct the vectors in the format the engine wants
	for (size_t id = 0; id < num_vertices; ++id) {
		locs.emplace_back(vertices[id].position.x, vertices[id].position.y);

		tex_coord.emplace_back(vertices[id].tex_coord.x, vertices[id].tex_coord.y);

		colors.emplace_back(vertices[id].colour.red, vertices[id].colour.green,
			vertices[id].colour.blue, vertices[id].colour.alpha);
	}

	auto mes = std::make_shared<mesh>(
		locs.data(), num_vertices, reinterpret_cast<glm::uvec3*>(indices), num_indices / 3);
	auto settings = new mesh_settings(mes, {m_shader});

	mes->add_additional_data("uv", tex_coord.data(), sizeof(glm::vec2) * tex_coord.size());
	mes->add_additional_data("color", colors.data(), sizeof(glm::vec4) * colors.size());

	// the property_values needs a shared pointer, so create one that won't delete it when it is
	// done
	auto shared_texture = std::shared_ptr<texture>(new texture, [](auto) {});
	shared_texture->texture_name = reinterpret_cast<texture*>(texturehandle)->texture_name;
	shared_texture->size = reinterpret_cast<texture*>(texturehandle)->size;
	settings->m_material.property_values["Texture"] = shared_texture;

	return reinterpret_cast<intptr_t>(settings);
}

// Called by Rocket when it wants to render application-compiled geometry.
void render_interface::RenderCompiledGeometry(
	Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
	glm::mat3 mvp = glm::ortho2d(0.f, (float)viewport_size.x, (float)viewport_size.y, 0.f);
	mvp = glm::translate(mvp, glm::vec2(translation.x, translation.y));

	auto m = reinterpret_cast<mesh_settings*>(geometry);

	m->render(mvp);
}

// Called by Rocket when it wants to release application-compiled geometry.
void render_interface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
	auto m = reinterpret_cast<mesh*>(geometry);

	delete m;
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
	glScissor(x, viewport_size.y - (y + height), width, height);
}

// Called by Rocket when a texture is required by the library.
bool render_interface::LoadTexture(Rocket::Core::TextureHandle& texture_handle,
	Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	try {
		auto texasset = m_asset_manager->get_asset<texture_asset>(source.CString());

		texture_dimensions = Rocket::Core::Vector2i(texasset->size.x, texasset->size.y);

		// make our own version because shared_ptr will delete it
		auto tex = new texture{};
		tex->size = texasset->size;
		tex->texture_name = texasset->texture_name;

		// make sure the texasset doesn't kill our GL objects
		texasset->texture_name = 0;

		texture_handle = reinterpret_cast<intptr_t>(tex);
	} catch (const std::exception& e) {
		return false;
	}

	return true;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of
// pixels.
bool render_interface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle,
	const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	try {
		auto ret = new texture(source, {source_dimensions.x, source_dimensions.y});

		texture_handle = reinterpret_cast<intptr_t>(ret);
	} catch (std::exception&) {
		return false;
	}

	return true;
}

// Called by Rocket when a loaded texture is no longer required.
void render_interface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	delete reinterpret_cast<texture*>(texture_handle);
}
}  // namespace ui
}  // namespace ge
