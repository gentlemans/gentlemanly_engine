#pragma once

#include <ge/actor.hpp>
#include "grid.hpp"
#include "toweractor.hpp"
#include "gridtick_interface.hpp"
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>

class zombie : public toweractor
{
public:
	
	ge::mesh_actor* m_mesh;
	
    void initialize(glm::uvec3 location) {
        toweractor::initialize(location);

        add_interface<zombie, gridtick_interface>();
		
		m_mesh = factory<ge::mesh_actor>(this, "texturedmodel/textured.meshsettings").get();
		m_mesh->m_mesh_settings.m_material.m_property_values["Texture"] = m_runtime->m_asset_manager.get_asset<ge::texture_asset>("zombie.texture");

    }

    void tick_grid() {
		std::cout << "Ticked!\n";
    }
};
