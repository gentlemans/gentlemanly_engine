#pragma once

#include <Box2D/Box2D.h>

#include "ge/actor.hpp"

namespace ge
{
class physics_controller
{
	friend class collision_body;

	b2Body* m_b2_body;

	actor* m_actor;

public:
	physics_controller(actor& actor_to_control);
	~physics_controller();

	actor& get_actor() const { return *m_actor; }
	void activate() { m_b2_body->SetActive(true); }
	void deactivate() { m_b2_body->SetActive(false); }
	bool get_active() const { return m_b2_body->IsActive(); }
	// TODO: this isn't complete
};
}
