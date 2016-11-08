#pragma once

#ifndef TURRET_HPP
#define TURRET_HPP

#include "piece.hpp"
#include "gridtick_interface.hpp"
#include "damagable.hpp"

#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>

class turret : public piece
{
	ge::mesh_actor* mesh;

public:
	void initialize(glm::uvec3 location)
	{
		piece::initialize(location);
		add_interface<turret, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
	}
	void tick_grid()
    {
        auto nearby = checkNearbySquares(get_grid_location());
        for (int x = 0; x < 4; x++)
        {
            Directions direction;
            if (nearby[x].size() != 0)
            {
                direction = Directions(x);
                rotate(direction);
            }

        }
	}
	void shoot()
	{
		auto d = tod->get_interface_storage<damagable>();
		if (d)
		{
			d->health -= 10;
		}
	}
};

#endif  // TURRET_HPP
