#ifndef GE_SYSTEM_INTERFACE_HPP
#define GE_SYSTEM_INTERFACE_HPP

#pragma once

#include "ge/runtime.hpp"

#include <Rocket/Core/SystemInterface.h>

namespace ge
{
namespace ui
{

class system_interface : public Rocket::Core::SystemInterface
{

public:
	system_interface(runtime& arg_app) {};

private:

	// TODO: reimplement
	virtual float GetElapsedTime() override { return 0;  }
};
}
}

#endif // GE_SYSTEM_INTERFACE_HPP
