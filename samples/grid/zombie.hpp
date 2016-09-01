#pragma once

#include <ge/actor.hpp>
#include "grid.hpp"

class zombie : public ge::actor
{
	glm::uvec2 m_location;

	grid* m_grid;

	zombie(grid& grid, glm::uvec2 location) : m_grid{&grid}, m_location{location} {}
};
