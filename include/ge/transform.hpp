#pragma once

#include <glm/glm.hpp>

namespace ge
{
struct transform
{
	glm::vec2 location = {0.f, 0.f};
	float rotation = 0.f;
	glm::vec2 scale = {1.f, 1.f};

	bool operator==(const transform& other)
	{
		return this->location == other.location && this->rotation == other.rotation &&
			   this->scale == other.scale;
	}

	bool operator!=(const transform& other) { return !(*this == other); }
};
}
