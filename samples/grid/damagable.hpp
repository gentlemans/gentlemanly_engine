#ifndef GE_GRID_DAMAGABLE_HPP
#define GE_GRID_DAMAGABLE_HPP

#pragma once

#include <iostream>

#include "piece.hpp"

struct damagable {
	struct interface_storage {
		interface_storage(float healtha, piece* p) : health{healtha} , pie(p) {}

		void damage(float amt) {
			health = health - amt;
			if (health <= 0)
				pie->sig_die(pie);
		}

		void regen(float amt) {

		}

	private:
		float health;

		piece* pie;
	};

	template <typename Actor>
	static std::shared_ptr<interface_storage> gen_interface(Actor* act, float health)
	{
		return std::make_shared<interface_storage>(health, static_cast<piece*>(act));
	}
};

#endif  // GE_GRID_DAMAGABLE_HPP
