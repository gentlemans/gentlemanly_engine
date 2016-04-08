#pragma once

#include <boost/concept_check.hpp>

#include <glm/glm.hpp>

#include <boost/signals2.hpp>

namespace ge
{

namespace concept
{

// the concept for subsystems
template<typename X>
struct Window
{
	BOOST_CONCEPT_USAGE(Window)
	{
		i.set_title("New title");
		std::string title = i_c.get_title();
		
		// operator bool
		bool does = i_c;
		
		boost::signals2::signal<void()>& quit = i.sig_quit;
	}
	
private:
	
	X i;
	const X i_c;
};

} // namespace concept

} // namespace ge
