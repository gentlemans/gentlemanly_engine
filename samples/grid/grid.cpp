#include "grid.hpp"

#include "base.hpp"

void grid::initialize(glm::uvec3 size)
{
	set_relative_location({-size.x / 2, -size.y / 2});

	m_size = size;

	towers.resize(size.x * size.y * size.z);

	getActorFromCoord({size.x / 2 + 1, size.y / 2 + 1, 2}) =
		ge::actor::factory<base>(this, glm::uvec3{size.x / 2 + 1, size.y / 2 + 1, 2}).get();
}
