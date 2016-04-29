#pragma once

#include <anax/anax.hpp>

#include <glm/glm.hpp>
#include <Box2D/Box2D.h>

#include "ge/transform.hpp"

namespace ge {


	
struct transform_component : anax::Component
{
	b2Body* body;
		
	transform get_transform() const
	{
		auto tmp = body->GetTransform();
		return {{tmp.p.x, tmp.p.y}, tmp.q.GetAngle()};
	}
	
	void set_transform(transform new_transform)
	{
		body->SetTransform({ new_transform.location.x, new_transform.location.y}, new_transform.rotation);
		
	}
	
	
};

}
