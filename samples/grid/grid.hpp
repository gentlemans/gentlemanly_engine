#pragma once

#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>

#include <memory>
#include <vector>

class piece;

class grid : public ge::actor
{
	glm::uvec3 m_size;

public:
	void initialize(glm::uvec3 size, float tps);

	std::vector<piece*> towers;

	piece*& getActorFromCoord(glm::uvec3 loc)
	{
		assert(loc.x < m_size.x);
		assert(loc.y < m_size.y);
		assert(loc.z < 3);
		return towers[loc.z * m_size.x * m_size.y + loc.y * m_size.x + loc.x];
	}
	glm::uvec2 get_size() const
	{
		return{ m_size.x, m_size.y };
	}
};
