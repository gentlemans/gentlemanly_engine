#ifndef GE_PIECE_HPP
#define GE_PIECE_HPP

#pragma once

#include <ge/actor.hpp>

class piece : public ge::actor
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
	void setGridLocation(glm::uvec3 loc)
	{
		m_grid->getActorFromCoord(m_loc) = NULL;
		m_loc = loc;
		set_relative_location({ loc.x, loc.y });
		m_grid->getActorFromCoord(m_loc) = this;
	}
};

#endif // GE_PIECE_HPP
