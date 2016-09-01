#pragma once

#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>

#include <memory>
#include <vector>

class toweractor;

class grid : public ge::actor
{
	glm::uvec2 m_size;

	ge::asset_manager* asset_man;

public:
	void initialize(glm::uvec2 size, ge::asset_manager& asset_m);

	std::vector<std::shared_ptr<toweractor>> towers;

	std::shared_ptr<toweractor>& getActorFromCoord(glm::uvec3 loc)
	{
		assert(loc.x < m_size.x);
		assert(loc.y < m_size.y);
		assert(loc.z < 3);
		return towers[loc.z * m_size.x * m_size.y + loc.y * m_size.x + loc.x];
	}
};
