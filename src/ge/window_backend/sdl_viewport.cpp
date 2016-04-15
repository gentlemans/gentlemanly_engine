#include "ge/window_backend/sdl_viewport.hpp"

#include "ge/window_backend/sdl_window.hpp"

#include "ge/actor.hpp"
#include "ge/camera.hpp"

#include "ge/ortho2d.hpp"

#include <GL/gl.h>

#include <stdexcept>

#include <glm/glm.hpp>

namespace ge
{
namespace window_backend
{
sdl_viewport::sdl_viewport(ge::window_backend::sdl_window* window_arg) : m_window{window_arg} {}
void sdl_viewport::set_background_color(const glm::vec4& newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

void sdl_viewport::render_actor(ge::actor* actor)
{
	if (!current_camera) throw std::runtime_error("Cannot call render_actor with a null camera");

	float aspect = (float)m_window->get_size().x / (float)m_window->get_size().y;

	glm::mat3 projection = glm::ortho2d(
		-aspect * current_camera->vertical_units, aspect * current_camera->vertical_units,
		-current_camera->vertical_units, current_camera->vertical_units);
	glm::mat3 vp = projection * current_camera->calculate_model_matrix();

	actor->render_tree(vp);
}

void sdl_viewport::set_camera(ge::camera* camera) { current_camera = camera; }
ge::camera* sdl_viewport::get_camera() const { return current_camera; }
}
}
