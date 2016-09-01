#ifndef GE_TOWERACTOR_HPP
#define GE_TOWERACTOR_HPP

#pragma once

#include <ge/actor.hpp>

class toweractor : public ge::actor
{
public:
	grid* m_grid;
	glm::uvec3 m_loc;

	void initialize(grid& g, glm::uvec3 loc)
	{
		m_grid = &g;
		m_loc = loc;
		set_parent(m_grid);
	}
};

#endif
