#pragma once

#include <glm/glm.hpp>

namespace ge {
namespace window_backend {

class sdl_viewport
{
public:
	void set_background_color(const glm::vec4& newColor);
};

} // namespace window_backend
} // namespace ge
