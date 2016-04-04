#pragma once


#include <SDL.h>

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
public:
	application()
	{
	}
};

} // namespace ge
