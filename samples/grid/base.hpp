#pragma once

#include <ge/asset_manager.hpp>
#include <ge/material.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/mesh_asset.hpp>
#include <ge/texture_asset.hpp>

#include "toweractor.hpp"

class base : public toweractor
{
public:
	std::shared_ptr<ge::mesh_actor> m_mesh;

	void initialize(glm::uvec3 loc)
	{
		toweractor::initialize(loc);


		m_mesh = ge::actor::factory<ge::mesh_actor>(this, "square");
	}
};
