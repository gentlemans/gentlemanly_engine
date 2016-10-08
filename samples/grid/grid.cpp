#include "grid.hpp"

#include "base.hpp"

void grid::initialize(glm::uvec3 size)
{
	set_relative_location(glm::vec2(-float(size.x) / 2.f, -float(size.y) / 2.f));

	m_size = size;

	towers.resize(size.x * size.y * size.z);

	getActorFromCoord({size.x / 2, size.y / 2, 2}) =
		ge::actor::factory<base>(this, glm::uvec3{size.x / 2, size.y / 2, 2}).get();
}
