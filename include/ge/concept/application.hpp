#pragma once

#include <boost/concept_check.hpp>

#include <boost/optional.hpp>

#include "ge/concept/window.hpp"
#include "ge/concept/viewport.hpp"

#include <memory>

#include <glm/glm.hpp>

namespace ge
{
namespace concept
{
// the concept for subsystems
template <typename X>
struct Application
{
	using window = typename X::window;
	using viewport = typename X::viewport;

	BOOST_CONCEPT_ASSERT((Window<window>));
	BOOST_CONCEPT_ASSERT((Viewport<viewport>));

	BOOST_CONCEPT_USAGE(Application)
	{
		const X& i_c = i;

		int argc;
		char** argv;
		X exp_construct(argc, argv);

		i.execute();

		std::unique_ptr<window> win = i.make_window("Title",  // title
			boost::optional<glm::uvec2>(),					  // location on sceen
			glm::uvec2(),									  // size
			true,											  // fullscreen
			false											  // decorated
			);

		std::unique_ptr<viewport> view = i.make_viewport(*win  // window
			);
		
		boost::signals2::signal<void(float)>& update = i.signal_update;
		boost::signals2::signal<void()>& init = i.signal_init;
	}

private:
	X i;
};

}  // namespace concept

}  // namespace ge
