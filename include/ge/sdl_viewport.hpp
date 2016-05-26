#pragma once
#include "ge/concept/viewport.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace ge
{
class camera_component;
class model_system;
class sdl_window;

class sdl_viewport
{
	sdl_window* m_window;

public:
	explicit sdl_viewport(sdl_window& window);

	void set_background_color(const glm::vec4& newColor);

	sdl_window& get_window() const { return *m_window; }
	
	input_event get_next_input_event();
	
};
BOOST_CONCEPT_ASSERT((concept::Viewport<sdl_viewport>));

}  // namespace ge
