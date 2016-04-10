#pragma once

#include <boost/concept_check.hpp>

#include <boost/optional.hpp>

#include "ge/concept/window.hpp"
#include "ge/concept/viewport.hpp"

#include <memory>

#include <glm/glm.hpp>

namespace ge
{

template<typename>
class application;

namespace concept
{

// the concept for subsystems
template<typename X>
struct WindowBackend
{
	using window = typename X::window;
	using viewport = typename X::viewport;
	
	BOOST_CONCEPT_ASSERT((Window<window>));
	BOOST_CONCEPT_ASSERT((Viewport<viewport>));
	
	BOOST_CONCEPT_USAGE(WindowBackend)
	{
		int argc;
		char** argv;
		X exp_construct(app, argc, argv);
		
		i.execute();
		
		std::unique_ptr<window> win = i.make_window(
			"Title", 						// title
			boost::optional<glm::uvec2>(), 	// location on sceen
			glm::uvec2(), 					// size
			true,							// fullscreen
			false 							// decorated
		);
		
		std::unique_ptr<viewport> view = i.make_viewport(
			*win	// window
		);
		
		
	}
	
private:
	application<X>& app;
	X i;
	const X i_c;
};

} // namespace concept

} // namespace ge
