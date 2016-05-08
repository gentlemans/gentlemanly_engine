#pragma once

#include <entityx/entityx.h>

#include "ge/model_component.hpp"
#include "ge/transform_component.hpp"

#include "ge/concept/viewport.hpp"
#include "ge/material.hpp"
#include "ge/mesh.hpp"
#include "ge/shader.hpp"

#include "ge/ortho2d.hpp"

#include <vector>
#include <algorithm>

namespace ge
{
struct model_system : entityx::System<model_system>
{
	model_system(float arg_aspect) : aspect{arg_aspect} {}
	float aspect;

	virtual void update(
		entityx::EntityManager& em, entityx::EventManager& events, entityx::TimeDelta) override;
};
}
