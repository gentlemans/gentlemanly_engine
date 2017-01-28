#pragma once

#include <ge/actor.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/runtime.hpp>
#include <ge/texture_asset.hpp>
#include <ge/shader_asset.hpp>
#include <ge/material_asset.hpp>
#include "grid.hpp"
#include "gridtick_interface.hpp"
#include "piece.hpp"

class zombie : public piece
{
	glm::ivec2 get_grid_center() { return {m_grid->get_size().x / 2, m_grid->get_size().y / 2}; }
	void damage_in_direction(Directions d);
	bool attacking;
public:
	ge::mesh_actor* m_mesh;

	boost::signals2::scoped_connection die_connect;
	boost::signals2::scoped_connection take_damage;
	ge::material zombie_mat;
	ge::material red_mat;

	void initialize(glm::ivec3 location, stats stat)
	{
		piece::initialize(location);
		now = stat;
		initial = stat;
		add_interface<zombie, gridtick_interface>();
		
		m_mesh = factory<ge::mesh_actor>(this, "texturedmodel/textured.meshsettings").get();
        m_mesh->m_mesh_settings.m_material.m_shader = m_runtime->m_asset_manager.get_asset<ge::shader_asset>("zombie.shader");
		m_mesh->m_mesh_settings.m_material.m_property_values["Texture"] =
			m_runtime->m_asset_manager.get_asset<ge::texture_asset>("zombie.texture");
        std::uniform_real_distribution<> dist{0, 2};
        m_mesh->m_mesh_settings.m_material.m_property_values["Discoloration"] = glm::vec3(dist(m_grid->rand_gen), dist(m_grid->rand_gen), dist(m_grid->rand_gen));

		zombie_mat = m_mesh->m_mesh_settings.m_material;

		red_mat = *m_runtime->m_asset_manager.get_asset<ge::material_asset>("solid.material");
		red_mat.set_parameter("Color", glm::vec4(1.f, 0.f, 0.f, 1.f));

		die_connect = sig_die.connect([this](piece* p) {
			m_grid->increment_z_count(false);
			p->set_parent(NULL);
		});
		m_grid->increment_z_count(true);
	}
	void damage(float damage) override
	{
		m_mesh->m_mesh_settings.m_material = red_mat;
		m_grid->timer->add_timer(1, [this] {
			m_mesh->m_mesh_settings.m_material = zombie_mat;
		}, shared(this));
		modify_health(-damage);
	}
	void move_closer_to_center();
	void move_random();
	void move_off_spawner();
	void tick_grid();
};
