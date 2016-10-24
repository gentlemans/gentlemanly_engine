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
    void initialize(glm::uvec2 size, float tps);

    std::vector<piece*> get_actors_from_coord(glm::uvec3 loc);

	glm::uvec2 get_size() const { return {m_size.x, m_size.y}; }
};
