#ifndef GE_SYSTEM_INTERFACE_HPP
#define GE_SYSTEM_INTERFACE_HPP

#pragma once

#include <Rocket/Core/SystemInterface.h>

#include "ge/concept/application.hpp"

namespace ge
{
namespace ui
{
template <typename Application>
class system_interface : public Rocket::Core::SystemInterface
{
	BOOST_CONCEPT_ASSERT((concept::Application<Application>));

public:
	system_interface(Application& arg_app) : app{arg_app} {};

private:
	Application& app;

	virtual float GetElapsedTime() override { return app.get_elapsed_time(); }
};
}
}

#endif // GE_SYSTEM_INTERFACE_HPP
