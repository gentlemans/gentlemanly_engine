#pragma once

#include "ge/actor.hpp"

namespace ge
{
class camera : public actor
{
public:
	camera(actor* parent) : actor(parent)
	{}
	
	float vertical_units = 10.f;
	
	~camera() = default;
};
}
