#include "ge/window_backend/sdl_viewport.hpp"

#include <GL/gl.h>

namespace ge  {
namespace window_backend {

void sdl_viewport::set_background_color(const glm::vec4& newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

}
}

