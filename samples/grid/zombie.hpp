#pragma once

#include <ge/actor.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>
#include <ge/runtime.hpp>
#include "damagable.hpp"
#include "grid.hpp"
#include "gridtick_interface.hpp"
#include "piece.hpp"

class zombie : public piece
{
	glm::ivec2 get_grid_center()
	{
		return { m_grid->get_size().x / 2, m_grid->get_size().y / 2 };
	}
public:
	ge::mesh_actor* m_mesh;

	void initialize(glm::ivec3 location)
	{
		piece::initialize(location);

		add_interface<zombie, gridtick_interface>();
		add_interface<zombie, damagable>(100.f);

		m_mesh = factory<ge::mesh_actor>(this, "texturedmodel/textured.meshsettings").get();
		m_mesh->m_mesh_settings.m_material.m_property_values["Texture"] =
			m_runtime->m_asset_manager.get_asset<ge::texture_asset>("zombie.texture");
	}
	void move_closer_to_center();
	void move_random();
	void tick_grid();
};
