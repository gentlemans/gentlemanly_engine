#include "ge/sdl_viewport.hpp"
#include "ge/sdl_window.hpp"
#include "ge/camera_component.hpp"
#include "ge/model_system.hpp"
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

void sdl_viewport::render(const model_system& models, const camera_component& camera)
{
	float aspect = (float)m_window->get_size().x / (float)m_window->get_size().y;

	glm::mat3 projection = glm::ortho2d(-aspect * camera.vertical_units,
		aspect * camera.vertical_units, -camera.vertical_units, camera.vertical_units);
	glm::mat3 vp = projection; // TODO:  * camera.calculate_model_matrix();
	
	for(auto& ent : models.entities)
	{
		ent.getComponent<model_component>().render(vp);
	}
	
}

}
