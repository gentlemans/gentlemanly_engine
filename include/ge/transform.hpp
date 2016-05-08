#pragma once

#include <glm/glm.hpp>

namespace ge
{
struct transform
{
	glm::vec2 location;
	float rotation;

	bool operator==(const transform& other)
	{
		return this->location == other.location && this->rotation == other.rotation;
	}

	bool operator!=(const transform& other) { return !(*this == other); }
};
}
