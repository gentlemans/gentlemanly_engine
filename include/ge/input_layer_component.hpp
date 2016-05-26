#pragma once

#include <functional>

#include "ge/input_event.hpp"

namespace ge
{
struct input_layer_component
{
	std::function<bool(input_event)> func;
};
}
