#ifndef GE_ROCKET_SUBSYSTEM_HPP
#define GE_ROCKET_SUBSYSTEM_HPP

#pragma once

#include "ge/subsystem.hpp"

namespace ge {

struct rocket_subsystem : subsystem {
	
	struct config{};
	
	bool initialize(config c);
	bool update(std::chrono::duration<float> delta) override;
	bool shutdown() override;
	
};

} // ge

#endif // GE_ROCKET_SUBSYSTEM_HPP
