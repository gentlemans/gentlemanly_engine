#include "ge/sdl_viewport.hpp"
#include "ge/sdl_window.hpp"
#include "ge/actor.hpp"
#include "ge/camera_actor.hpp"
#include "ge/world.hpp"

#include "ge/ortho2d.hpp"

#include "SDL.h"

#include <GL/gl.h>

#include <stdexcept>

#include <glm/glm.hpp>

namespace ge
{
sdl_viewport::sdl_viewport(ge::sdl_window& window_arg) : m_window{&window_arg} {}
void sdl_viewport::set_background_color(const glm::vec4& newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

void sdl_viewport::render()
{
	if (!m_camera) throw std::runtime_error("Cannot call render_actor with a null camera");
	if (!m_world) throw std::runtime_error("Cannot call render_actor with a null world");

	float aspect = (float)m_window->get_size().x / (float)m_window->get_size().y;

	glm::mat3 projection = glm::ortho2d(-aspect * m_camera->vertical_units,
		aspect * m_camera->vertical_units, -m_camera->vertical_units, m_camera->vertical_units);
	glm::mat3 vp = projection * m_camera->calculate_model_matrix();

	m_world->for_each_actor([&vp](actor* actor_to_render)
		{
			actor_to_render->render(vp);
		});
}

}
