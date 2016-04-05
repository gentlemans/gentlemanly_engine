#pragma once


#include <SDL.h>

#include <tuple>
// for shared_ptr
#include <memory>

// for for_each and find
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/fusion/algorithm.hpp>

#include "gentlemanly_engine/concept/subsystem.hpp"
#include "gentlemanly_engine/concept/variadic_concept.hpp"

namespace ge
{

// the Subsystems to be loaded
template<typename... _Subsystems>
class application
{
	// check concepts
	BOOST_CONCEPT_ASSERT((concept::variadic_concept<concept::Subsystem, _Subsystems...>));
	
	std::tuple<std::shared_ptr<_Subsystems>...> m_subsystems;
	
public:
	application(const std::shared_ptr<_Subsystems>&... arg_subsystems)
		:m_subsystems{ arg_subsystems... }
	{
		
		// get flags from subsystems
		Uint16 flags = 0;
		boost::fusion::for_each(m_subsystems, [&flags](auto& subsystem){
			flags = subsystem->get_sdl_init_flags();
		});
		
		SDL_Init(flags);
	}
	
	// move only
	application(const application&) = delete;
	application(application&&) = default;
	
	application& operator=(const application&) = delete;
	application& operator=(application&&) = default;
	
	// destructor
	~application()
	{
		SDL_Quit();
	}
	
	// subsystem interop
	template<typename subsystem>
	std::shared_ptr<subsystem> get_subsystem()
	{
		return *boost::fusion::find<std::shared_ptr<subsystem>>(m_subsystems);
	}
	
	
};

} // namespace ge
