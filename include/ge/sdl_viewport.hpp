#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace ge
{
class camera;
class world;

class sdl_window;

class sdl_viewport
{
	camera* m_camera = nullptr;
	sdl_window* m_window;
	std::unique_ptr<world> m_world = nullptr;

public:
	explicit sdl_viewport(sdl_window& window);

	void set_background_color(const glm::vec4& newColor);

	void render();

	camera& get_camera() const { return *m_camera; }
	void set_camera(camera& new_camera) { m_camera = &new_camera; }
	world& get_world() const { return *m_world; }
	void set_world(std::unique_ptr<world>&& new_world) { m_world = std::move(new_world); }
};

}  // namespace ge
