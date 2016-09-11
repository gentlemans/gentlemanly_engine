#ifndef GE_ROCKET_INPUT_CONSUMER_HPP
#define GE_ROCKET_INPUT_CONSUMER_HPP

#pragma once

#include "ge/input_consumer.hpp"

#include <Rocket/Core/Context.h>

namespace ge
{
namespace ui
{
/// This input consumer passes all input to Rocket
struct rocket_input_consumer : input_consumer<rocket_input_consumer> {
	/// The constructor from the context
	rocket_input_consumer(Rocket::Core::Context* con) : m_context{con} {}
	/// The handle that gets called from `input_consumer`
	void handle_input(const input_event& event);

	/// The Rocket context
	Rocket::Core::Context* m_context;
};
}
}

#endif  // GE_ROCKET_INPUT_CONSUMER_HPP
