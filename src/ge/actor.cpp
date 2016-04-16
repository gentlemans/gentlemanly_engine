#include "ge/actor.hpp"

#include <stdexcept>
#include <algorithm>

#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace ge
{
actor::actor(actor* arg_parent) : parent{arg_parent}
{
	if (parent)
	{
		parent->children.insert(this);
	}
}

actor::~actor()
{
	if (parent)
	{
		parent->children.erase(this);
	}
}

glm::vec2 actor::calcuate_absolute_location() const
{
	glm::vec2 parent_loc = parent ? parent->calcuate_absolute_location() : glm::vec2{0, 0};
	float parent_rot = parent ? parent->calcuate_absolute_rotation() : 0.f;

	return parent_loc + glm::rotate(relative_location, parent_rot);
}

float actor::calcuate_absolute_rotation() const
{
	return relative_rotation + (parent ? parent->calcuate_absolute_rotation() : 0);
}

glm::vec2 actor::calcuate_absolute_scale() const
{
	return relative_scale * (parent ? parent->calcuate_absolute_scale() : glm::vec2(1.f, 1.f));
}

glm::mat3 actor::calculate_model_matrix() const
{
	glm::mat3 this_model;

	glm::scale(this_model, relative_scale);
	glm::translate(this_model, relative_location);
	glm::rotate(this_model, relative_rotation);

	return parent ? this_model * parent->calculate_model_matrix() : this_model;
}

}  // namespace ge
