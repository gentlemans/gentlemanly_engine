#pragma once

namespace ge
{
struct camera_component
{
	camera_component(float arg_vert_units) : vertical_units{arg_vert_units} {}
	float vertical_units;
};
}
