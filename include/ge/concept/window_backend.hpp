#pragma once

#include <boost/concept_check.hpp>

#include <boost/optional.hpp>

#include "ge/concept/window.hpp"
#include "ge/concept/viewport.hpp"

#include <memory>

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
		
		std::unique_ptr<window> win = i.create_window(
			"Title", 						// title
			boost::optional<glm::uvec2>(), 	// location on sceen
			glm::uvec2(), 					// size
			true,							// fullscreen
			false 							// decorated
		);
		
	}
	
private:
	application<X>& app;
	X i;
	const X i_c;
};

} // namespace concept

} // namespace ge
