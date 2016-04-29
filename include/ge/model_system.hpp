#pragma once

#include "ge/model_component.hpp"

#include <anax/anax.hpp>

#include <vector>
#include <algorithm>

namespace ge {

struct model_system : anax::System<anax::Requires<model_component>>
{
	virtual void onEntityAdded(anax::Entity& ent)
	{
		entities.push_back(ent);
	}
	
	virtual void onEntityRemoved(anax::Entity& ent)
	{
		entities.erase(std::find(entities.begin(), entities.end(), ent));
	}
	
	// anax::Entity objects are really just pointers, so they don't copy underlying data
	std::vector<anax::Entity> entities;
	
	void render_all(const camera_component& cam)
	{
		
	}
};

}
