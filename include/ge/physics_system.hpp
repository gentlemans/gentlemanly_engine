#pragma once

#include <entityx/System.h>

#include <Box2D/Box2D.h>

#include "ge/transform_component.hpp"
#include "ge/velocity_component.hpp"

namespace ge
{
// inits the b2Body
struct physics_system : entityx::System<physics_system>, entityx::Receiver<physics_system>
{
	b2World m_b2_world{{3.f, 0.f}};

	virtual void configure(entityx::EventManager& events) override
	{
		events.subscribe<entityx::ComponentAddedEvent<transform_component>>(*this);
		events.subscribe<entityx::ComponentRemovedEvent<transform_component>>(*this);
	}

	virtual void update(
		entityx::EntityManager& entities, entityx::EventManager& events, double dt) override
	{
		m_b2_world.Step(dt, 1, 1);

		// assign the new locations
		entityx::ComponentHandle<transform_component> comp;
		for (auto ent : entities.entities_with_components(comp))
		{
			comp.get()->synchronize();
		}
	}

	// events
	void receive(const entityx::ComponentAddedEvent<transform_component>& event)
	{
		auto ev_cpy = event;  // we need this becaues it is a const ref :(
		auto& component = *ev_cpy.component.get();

		b2BodyDef def;
		def.type = component.get_simulate_physics() ? b2BodyType::b2_dynamicBody
													: b2BodyType::b2_staticBody;
		def.userData = &component;

		component.m_b2_body = m_b2_world.CreateBody(&def);
	}

	void receive(const entityx::ComponentRemovedEvent<transform_component>& event)
	{
		m_b2_world.DestroyBody(event.component.get()->m_b2_body);
	}
};
}
