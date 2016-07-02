#ifndef GE_ROCKET_INPUT_CONSUMER_HPP
#define GE_ROCKET_INPUT_CONSUMER_HPP

#pragma once

#include "ge/input_consumer.hpp"

#include <Rocket/Core/Context.h>

namespace ge
{
namespace ui
{
struct rocket_input_consumer : input_consumer<rocket_input_consumer> {
	rocket_input_consumer(Rocket::Core::Context* con) : m_context{con} {}
	void handle_input(const input_event& event);

	Rocket::Core::Context* m_context;
};
}
}

#endif // GE_ROCKET_INPUT_CONSUMER_HPP
