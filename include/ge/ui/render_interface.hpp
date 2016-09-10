#ifndef GE_RENDER_INTERFACE_HPP
#define GE_RENDER_INTERFACE_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/sdl_subsystem.hpp"
#include "ge/shader.hpp"
#include "ge/shader_asset.hpp"

#include <glm/glm.hpp>

#include "Rocket/Core/RenderInterface.h"

#include <memory>

namespace ge
{
namespace ui
{
class render_interface : public Rocket::Core::RenderInterface
{
	std::shared_ptr<shader> m_shader;

public:
	render_interface(asset_manager& asset_man, sdl_subsystem& sdl_sub) : m_asset_manager{&asset_man}
	{
		m_shader = asset_man.get_asset<shader_asset>("texturedmodel/textured.shader");

		viewport_size = sdl_sub.get_size();
	}

private:
	/// Called by Rocket when it wants to render geometry that it does not wish to optimise.
	virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices,
		int num_indices, Rocket::Core::TextureHandle texture,
		const Rocket::Core::Vector2f& translation);

	/// Called by Rocket when it wants to compile geometry it believes will be static for the
	/// forseeable future.
	virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices,
		int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

	/// Called by Rocket when it wants to render application-compiled geometry.
	virtual void RenderCompiledGeometry(
		Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
	/// Called by Rocket when it wants to release application-compiled geometry.
	virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

	/// Called by Rocket when it wants to enable or disable scissoring to clip content.
	virtual void EnableScissorRegion(bool enable);
	/// Called by Rocket when it wants to change the scissor region.
	virtual void SetScissorRegion(int x, int y, int width, int height);

	/// Called by Rocket when a texture is required by the library.
	virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle,
		Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
	/// Called by Rocket when a texture is required to be built from an internally-generated
	/// sequence of pixels.
	virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle,
		const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
	/// Called by Rocket when a loaded texture is no longer required.
	virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

	glm::uvec2 viewport_size;

private:
	asset_manager* m_asset_manager;
};
}
}

#endif  // GE_RENDER_INTERFACE_HPP
