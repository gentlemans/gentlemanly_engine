#include "grid.hpp"

#include "base.hpp"

void grid::initialize(glm::uvec2 size, ge::asset_manager& man)
{
	m_size = size;
	asset_man = &man;

	towers.resize(size.x * size.y * 3);

	getActorFromCoord({size.x / 2 + 1, size.y / 2 + 1, 2}) = ge::actor::factory<base>(
		this, *this, glm::uvec3{size.x / 2 + 1, size.y / 2 + 1, 2}, *asset_man);
}
