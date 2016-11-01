#include "ge/rocket_render_interface.hpp"
#include "ge/asset_manager.hpp"
#include "ge/gl.hpp"
#include "ge/log.hpp"
#include "ge/material.hpp"
#include "ge/mesh.hpp"
#include "ge/mesh_settings.hpp"
#include "ge/ortho2d.hpp"
#include "ge/runtime.hpp"
#include "ge/texture.hpp"
#include "ge/texture_asset.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Rocket/Core.h>
#include <Rocket/Core/FileInterface.h>

#include <ge/lodepng.h>

#include <memory>

using namespace ge;

// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void rocket_render_interface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices,
	int* indices, int num_indices, const Rocket::Core::TextureHandle texture,
	const Rocket::Core::Vector2f& translation)
{
	// translate into better data
	std::vector<glm::vec2> pos;
	std::vector<glm::vec2> uv;
	std::vector<glm::uvec3> indicies_vec;

	for (auto idx = 0ull; idx < (unsigned int)num_vertices; ++idx) {
		pos.emplace_back(vertices[idx].position.x, vertices[idx].position.y);
		uv.emplace_back(vertices[idx].tex_coord.x, vertices[idx].tex_coord.y);
	}

	for (auto idx = 0; idx < num_indices; idx += 3) {
		indicies_vec.emplace_back(indices[idx], indices[idx + 1], indices[idx + 2]);
	}

	auto me =
		std::make_shared<mesh>(pos.data(), pos.size(), indicies_vec.data(), indicies_vec.size());
	material mat(m_shader);

	if (texture) {
		mat.set_parameter("Texture", *reinterpret_cast<std::shared_ptr<ge::texture>*>(texture));
	}
	mesh_settings set(me, mat);

	glm::mat3 mvp;
	mvp = glm::translate(mvp, glm::vec2(translation.x, translation.y));

	set.render(mvp);
}

Rocket::Core::CompiledGeometryHandle rocket_render_interface::CompileGeometry(
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
	for (size_t id = 0ull; id < (unsigned int)num_vertices; ++id) {
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
	if (texturehandle) {
		settings->m_material.set_parameter(
			"Texture", *reinterpret_cast<std::shared_ptr<texture>*>(texturehandle));
	}
	return reinterpret_cast<intptr_t>(settings);
}

// Called by Rocket when it wants to render application-compiled geometry.
void rocket_render_interface::RenderCompiledGeometry(
	Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
	glm::mat3 mvp = glm::ortho2d(0.f, (float)viewport_size.x, (float)viewport_size.y, 0.f);
	mvp = glm::translate(mvp, glm::vec2(translation.x, translation.y));

	auto m = reinterpret_cast<mesh_settings*>(geometry);

	m->render(mvp);
}

// Called by Rocket when it wants to release application-compiled geometry.
void rocket_render_interface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
	auto m = reinterpret_cast<mesh_settings*>(geometry);

	delete m;
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.
void rocket_render_interface::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

// Called by Rocket when it wants to change the scissor region.
void rocket_render_interface::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, viewport_size.y - (y + height), width, height);
}

// Called by Rocket when a texture is required by the library.
bool rocket_render_interface::LoadTexture(Rocket::Core::TextureHandle& texture_handle,
	Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	using namespace std::string_literals;

	assert(boost::filesystem::path(source.CString()).extension() == ".png");

	try {
		std::vector<unsigned char> PNGData;
		unsigned width, height;

		boost::filesystem::path p(source.CString());
		assert(boost::filesystem::is_regular_file(p));

		// load PNG data
		auto err = lodepng::decode(PNGData, width, height, p.string().c_str());
		if (err != 0) {
			logger->error("Failed to load PNG: error: "s + lodepng_error_text(err));
			return false;
		}

		texture_dimensions = {int(width), int(height)};

		auto tex = new std::shared_ptr<texture>{
			new texture(PNGData.data(), {width, height}, "Rocket: "s + source.CString())};

		texture_handle = reinterpret_cast<uintptr_t>(tex);
	} catch (const std::exception&) {
		return false;
	}

	logger->info("Loaded image "s + source.CString() + " for rocket.");

	return true;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of
// pixels.
bool rocket_render_interface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle,
	const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	try {
		auto ret = new std::shared_ptr<texture>(new texture(
			source, {source_dimensions.x, source_dimensions.y}, "Generated Rocket Texture"));

		texture_handle = reinterpret_cast<intptr_t>(ret);
	} catch (std::exception&) {
		return false;
	}

	return true;
}

// Called by Rocket when a loaded texture is no longer required.
void rocket_render_interface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	delete reinterpret_cast<texture*>(texture_handle);
}
