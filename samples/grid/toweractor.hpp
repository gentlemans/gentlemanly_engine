#ifndef GE_TOWERACTOR_HPP
#define GE_TOWERACTOR_HPP

#pragma once

#include <ge/actor.hpp>

class toweractor : public ge::actor
{
public:
	grid* m_grid;
	glm::uvec3 m_loc;

	void initialize(glm::uvec3 loc)
	{
		m_grid = static_cast<grid*>(get_parent());
		m_loc = loc;
		set_parent(m_grid);
		set_relative_location({float(loc.x), float(loc.y)});
	}
};

#endif
