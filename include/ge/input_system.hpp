#pragma once

#include "ge/input_layer_component.hpp"

#include <entityx/entityx.h>

#include "ge/concept/viewport.hpp"

namespace ge {

template<typename Viewport>
struct input_system : entityx::System<input_system<Viewport>>
{
	
	BOOST_CONCEPT_ASSERT((concept::Viewport<Viewport>));
	
	Viewport& m_viewport;
	
	input_system(Viewport& viewport) : m_viewport{viewport} {
		
	}
	
	virtual void update(entityx::EntityManager& em, entityx::EventManager& events, entityx::TimeDelta) override {
		
		
		
		
	}
};

}

