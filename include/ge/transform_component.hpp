#pragma once

#include <anax/anax.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <Box2D/Box2D.h>

#include "ge/transform.hpp"

#include <boost/optional.hpp>

namespace ge {


	
struct transform_component : anax::Component
{
	b2Body* body;
	
	boost::optional<anax::Entity> parent;
	
	transform get_local_transform() const
	{
		auto tmp = body->GetTransform();
		return {{tmp.p.x, tmp.p.y}, tmp.q.GetAngle()};
	}
	
	void set_transform(transform new_transform)
	{
		body->SetTransform({ new_transform.location.x, new_transform.location.y}, new_transform.rotation);
		
	}
	
	transform calculate_absolute_transform() const {
		if(parent){
			auto parent_trans = parent->getComponent<transform_component>().calculate_absolute_transform();
			auto local_trans = get_local_transform();
			
			transform abs_trans;
			abs_trans.location = glm::rotate(glm::radians(parent_trans.rotation), local_trans.location) + parent_trans.location;
			abs_trans.rotation = local_trans.rotation + parent_trans.rotation;
			
			return abs_trans;
		}
		else {
			return get_local_transform();
		}
	}
	
	
	glm::mat3 calculate_model_matrix() const {
		
	}
	
	
};

}
