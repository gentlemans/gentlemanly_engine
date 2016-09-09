#pragma once

#ifndef TURRET_HPP
#define TURRET_HPP

#include "toweractor.hpp"

#include <ge/mesh_actor.hpp>
#include <ge/mesh.hpp>
#include <ge/texture_asset.hpp>

class turret : public toweractor {
	
	ge::mesh_actor* mesh;
	
public:
	
	void initialize(glm::uvec3 location) {
		toweractor::initialize(location);
		
		mesh = ge::actor::factory<ge::mesh_actor>(this, "square").get();
		mesh->m_mesh->m_material.property_values["Texture"] = m_runtime->m_asset_manager.get_asset<ge::texture_asset>("turret");
	}
	
	
	
};

#endif // TURRET_HPP
