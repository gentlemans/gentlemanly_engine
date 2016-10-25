#ifndef GE_GRID_DAMAGABLE_HPP
#define GE_GRID_DAMAGABLE_HPP

#pragma once

#include <iostream>

struct damagable {
	struct interface_storage {
		interface_storage(float health) : m_health{health} {}
		float m_health;
	};

	template <typename Actor>
	static std::shared_ptr<interface_storage> gen_interface(Actor* act, float health)
	{
		return std::make_shared<interface_storage>(health);
	}
};

#endif  // GE_GRID_DAMAGABLE_HPP
