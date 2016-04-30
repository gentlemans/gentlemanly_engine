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

}
