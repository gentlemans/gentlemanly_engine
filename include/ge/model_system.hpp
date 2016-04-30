#pragma once

#include "ge/model_component.hpp"
#include "ge/transform_component.hpp"

#include "ge/concept/viewport.hpp"
#include "ge/material.hpp"
#include "ge/mesh.hpp"
#include "ge/shader.hpp"

#include "ge/ortho2d.hpp"

#include <anax/anax.hpp>

#include <vector>
#include <algorithm>

namespace ge {

struct model_system : anax::System<anax::Requires<model_component, transform_component>>
{
	virtual void onEntityAdded(anax::Entity& ent) override
	{
		entities.push_back(ent);
	}
	
	virtual void onEntityRemoved(anax::Entity& ent) override 
	{
		entities.erase(std::find(entities.begin(), entities.end(), ent));
	}
	
	// anax::Entity objects are really just pointers, so they don't copy underlying data
	std::vector<anax::Entity> entities;
	
	
	void render_all(const anax::Entity& camera, float aspect);
};

}
