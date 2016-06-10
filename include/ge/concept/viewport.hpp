#pragma once

#include <boost/concept_check.hpp>

#include <glm/glm.hpp>

#include "ge/input_event.hpp"

#include <memory>
#include <vector>

namespace ge
{
namespace concept
{
template <typename X>
struct Viewport {
	using application = typename X::application;
	using window = typename X::window;

	BOOST_CONCEPT_USAGE(Viewport)
	{
		const X& i_c = i;

		i.set_background_color(glm::vec4{});

		std::vector<input_event> ev = i.get_input_events();

		float aspect = i_c.get_aspect_ratio();
		glm::uvec2 size = i_c.get_size();

		window& win = i.get_window();
		const window& cwin = i_c.get_window();
	}

private:
	X i;
};

}  // namespace concept

}  // namespace ge
