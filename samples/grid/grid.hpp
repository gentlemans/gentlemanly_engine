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

	std::vector<piece*> getActorFromCoord(glm::uvec3 loc)
	{
		assert(loc.x < m_size.x);
		assert(loc.y < m_size.y);
		assert(loc.z < 3);

		std::vector<piece*> ret;

		for (auto& child : m_children) {

			piece*  p = dynamic_cast<piece*>(child.get());
			if (!p) continue;

			if (p->get_relative_location() == glm::vec2{ loc.x, loc.y } && p->m_depth == loc.z) {
				ret.push_back(p);
			}
		}

		return ret;

	}
	glm::uvec2 get_size() const
	{
		return{ m_size.x, m_size.y };
	}
};
