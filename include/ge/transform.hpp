#ifndef GE_TRANSFORM_HPP
#define GE_TRANSFORM_HPP

#pragma once

#include <glm/glm.hpp>

namespace ge
{
/// A structure representing a place, rotation, and scale
struct transform {
	/// The location
	glm::vec2 location = {0.f, 0.f};

	/// The rotation, in degrees clockwise
	float rotation = 0.f;

	/// The scale
	glm::vec2 scale = {1.f, 1.f};

	/// Equality comparaision
	bool operator==(const transform& other)
	{
		return this->location == other.location && this->rotation == other.rotation &&
			   this->scale == other.scale;
	}

	/// Inequality comparision
	bool operator!=(const transform& other) { return !(*this == other); }
};
}

#endif  // GE_TRANSFORM_HPP
