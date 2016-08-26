#pragma once

#include <ge/mesh_actor.hpp>
#include <ge/asset_manager.hpp>
#include <ge/mesh_asset.hpp>
#include <ge/texture_asset.hpp>
#include <ge/material.hpp>

#include "toweractor.hpp"

class base : public toweractor {
public:
	
	std::shared_ptr<ge::mesh_actor> m_mesh;
	
	void initialize(grid& g, glm::uvec3 loc, ge::asset_manager& man)  {
		toweractor::initialize(g, loc);
		
		auto mesh = man.get_asset<ge::mesh_asset>("square");
		
		auto texture = man.get_asset<ge::texture_asset>("base_texture");
		
		mesh->m_material->property_values["Texture"] = texture;

		m_mesh = ge::actor::factory<ge::mesh_actor>(this, mesh);
		
	}
	
};
