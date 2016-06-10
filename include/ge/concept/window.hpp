#pragma once

#include <boost/concept_check.hpp>

#include <glm/glm.hpp>

#include <boost/signals2.hpp>

namespace ge
{
namespace concept
{
// the concept for subsystems
template <typename X>
struct Window {
	using application = typename X::application;
	using window = typename X::window;

	BOOST_CONCEPT_USAGE(Window)
	{
		const X& i_c = i;

		i.set_title("New title");
		std::string title = i_c.get_title();

		i.set_size(glm::uvec2(100, 200));
		glm::uvec2 size = i_c.get_size();

		application& app = i.get_application();
		const application& capp = i_c.get_application();
	}

private:
	X i;
};

}  // namespace concept

}  // namespace ge
