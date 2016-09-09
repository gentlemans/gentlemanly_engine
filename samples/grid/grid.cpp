#include "grid.hpp"

#include "base.hpp"

void grid::initialize(glm::uvec2 size)
{
	m_size = size;

	towers.resize(size.x * size.y * 3);

	getActorFromCoord({size.x / 2 + 1, size.y / 2 + 1, 2}) = ge::actor::factory<base>(
		this, glm::uvec3{size.x / 2 + 1, size.y / 2 + 1, 2}).get();
}
