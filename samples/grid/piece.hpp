#ifndef GE_PIECE_HPP
#define GE_PIECE_HPP

#pragma once

#include <ge/actor.hpp>
#include "grid.hpp"

class piece : public ge::actor
{
public:
	grid* m_grid;
	int m_level;
	std::array<std::vector<piece*>, 4> checkNearbySquares(glm::ivec2 myLocation);
	void initialize(glm::ivec3 loc)
	{
		m_grid = static_cast<grid*>(get_parent());
		set_parent(m_grid);
		set_relative_location({float(loc.x), float(loc.y)});
		m_level = loc.z;
	}
	void set_grid_location(glm::ivec3 loc)
	{
		set_relative_location({loc.x, loc.y});
		m_level = loc.z;
	}
	glm::ivec3 get_grid_location() const
	{
		return {int(get_relative_location().x), int(get_relative_location().y), m_level};
	}
};

#endif  // GE_PIECE_HPP
