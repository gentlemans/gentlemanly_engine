#pragma once

#include <ge/actor.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/runtime.hpp>
#include <ge/texture_asset.hpp>
#include <ge/material_asset.hpp>
#include "damagable.hpp"
#include "grid.hpp"
#include "gridtick_interface.hpp"
#include "piece.hpp"

class zombie : public piece
{
	glm::ivec2 get_grid_center() { return {m_grid->get_size().x / 2, m_grid->get_size().y / 2}; }
public:
	ge::mesh_actor* m_mesh;

	boost::signals2::scoped_connection die_connect;
	boost::signals2::scoped_connection take_damage;
	ge::material zombie_mat;
	ge::material red_mat;
	void initialize(glm::ivec3 location)
	{
		piece::initialize(location);

		add_interface<zombie, gridtick_interface>();
		add_interface<zombie, damagable>(100.f);  // 100 starting health

		m_mesh = factory<ge::mesh_actor>(this, "texturedmodel/textured.meshsettings").get();
		m_mesh->m_mesh_settings.m_material.m_property_values["Texture"] =
			m_runtime->m_asset_manager.get_asset<ge::texture_asset>("zombie.texture");

		zombie_mat = m_mesh->m_mesh_settings.m_material;

		red_mat = *m_runtime->m_asset_manager.get_asset<ge::material_asset>("solid.material");
		red_mat.set_parameter("Color", glm::vec4(1.f, 0.f, 0.f, 1.f));

		take_damage = sig_damaged.connect([this](piece* p, float amt) {
			m_mesh->m_mesh_settings.m_material = red_mat;
			m_grid->timer->addTimer(1, [this] {
				m_mesh->m_mesh_settings.m_material = zombie_mat;
			});
		});

		die_connect = sig_die.connect([](piece* p) {
			p->set_parent(NULL);
		});
	}
	void move_closer_to_center();
	void move_random();
	void tick_grid();
};
