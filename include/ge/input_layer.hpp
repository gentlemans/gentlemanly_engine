#pragma once

#include <functional>

#include "ge/input_event.hpp"

namespace ge
{
struct input_layer
{
	std::function<bool(input_event)> func;
};
}
