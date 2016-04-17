#include "ge/actor.hpp"
#include "ge/world.hpp"

#include <stdexcept>
#include <algorithm>

#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace ge
{
actor::actor(world& arg_containing_world, actor* arg_parent)
	: m_parent{arg_parent}, m_world{&arg_containing_world}
{
	if (m_parent)
	{
		m_parent->m_children.insert(this);
	}
	
	if(m_world->empty_slots.size() != 0)
	{
		m_world->actors[m_world->empty_slots.back()] = this;
		m_id_in_world = m_world->empty_slots.back();
		m_world->empty_slots.pop_back();
	}else{
		m_world->actors.push_back(this);
		m_id_in_world = m_world->actors.size();
	}
}

actor::~actor()
{
	if (m_parent)
	{
		m_parent->m_children.erase(this);
	}
	
	
}

glm::vec2 actor::calcuate_absolute_location() const
{
	glm::vec2 parent_loc = m_parent ? m_parent->calcuate_absolute_location() : glm::vec2{0, 0};
	float parent_rot = m_parent ? m_parent->calcuate_absolute_rotation() : 0.f;

	return parent_loc + glm::rotate(relative_location, parent_rot);
}

float actor::calcuate_absolute_rotation() const
{
	return relative_rotation + (m_parent ? m_parent->calcuate_absolute_rotation() : 0);
}

glm::vec2 actor::calcuate_absolute_scale() const
{
	return relative_scale * (m_parent ? m_parent->calcuate_absolute_scale() : glm::vec2(1.f, 1.f));
}

glm::mat3 actor::calculate_model_matrix() const
{
	glm::mat3 this_model;

	glm::scale(this_model, relative_scale);
	glm::translate(this_model, relative_location);
	glm::rotate(this_model, relative_rotation);

	return m_parent ? this_model * m_parent->calculate_model_matrix() : this_model;
}

}  // namespace ge
