#pragma once
#include "ge/concept/viewport.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace ge
{
class sdl_window;
class sdl_application;

class sdl_viewport
{
	sdl_window* m_window;

public:
	using application = sdl_application;
	using window = sdl_window;

	window& get_window() { return *m_window; }
	const window& get_window() const { return *m_window; }
	explicit sdl_viewport(sdl_window& window);

	void set_background_color(const glm::vec4& newColor);

	std::vector<input_event> get_input_events();

	glm::uvec2 get_size() const;
	float get_aspect_ratio() const;
};
BOOST_CONCEPT_ASSERT((concept::Viewport<sdl_viewport>));

}  // namespace ge
