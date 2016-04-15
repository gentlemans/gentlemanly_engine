#pragma once

#include <glm/glm.hpp>

namespace ge
{
class camera;
class actor;

namespace window_backend
{
class sdl_window;

class sdl_viewport
{
	camera* current_camera = nullptr;

	sdl_window* m_window;
	
	actor* root;

public:
	explicit sdl_viewport(sdl_window* window);

	void set_background_color(const glm::vec4& newColor);

	void render();

	void set_camera(camera* camera);
	camera* get_camera() const;
	
	actor* root_actor(){ return root; }
	const actor* root_actor() const{ return root; }
};

}  // namespace window_backend
}  // namespace ge
