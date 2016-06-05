#pragma once

#include "ge/actor.hpp"

namespace ge
{
struct camera_actor
{
	void initialize(float arg_vert_units) {
		m_vertical_units = arg_vert_units; 
	}
	float m_vertical_units;
};
}
