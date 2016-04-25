#include "ge/entity.hpp"
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
	if (has_parent())
	{
		get_parent().m_children.insert(this);
	}

	if (get_world().empty_slots.size() != 0)
	{
		get_world().actors[get_world().empty_slots.back()] = this;
		m_id_in_world = get_world().empty_slots.back();
		get_world().empty_slots.pop_back();
	}
	else
	{
		get_world().actors.push_back(this);
		m_id_in_world = get_world().actors.size();
	}
}

actor::~actor()
{
	if (has_parent())
	{
		get_parent().m_children.erase(this);
	}
	
	get_world().empty_slots.push_back(m_id_in_world);
}

glm::vec2 actor::calcuate_absolute_location() const
{
	glm::vec2 parent_loc = has_parent() ? get_parent().calcuate_absolute_location() : glm::vec2{0, 0};
	float parent_rot = has_parent() ? get_parent().calcuate_absolute_rotation() : 0.f;

	return parent_loc + glm::rotate(m_relative_location * (has_parent() ? get_parent().calcuate_absolute_scale() : glm::vec2(1.f, 1.f)), glm::radians(parent_rot));
}

float actor::calcuate_absolute_rotation() const
{
	return m_relative_rotation + (has_parent() ? get_parent().calcuate_absolute_rotation() : 0.f);
}

glm::vec2 actor::calcuate_absolute_scale() const
{
	return m_relative_scale * (has_parent() ? get_parent().calcuate_absolute_scale() : glm::vec2(1.f, 1.f));
}

glm::mat3 actor::calculate_model_matrix() const
{
	glm::mat3 this_model;

	glm::scale(this_model, m_relative_scale);
	glm::translate(this_model, m_relative_location);
	glm::rotate(this_model, m_relative_rotation);

	return has_parent() ? this_model * get_parent().calculate_model_matrix() : this_model;
}

void ge::actor::set_absolute_location(glm::vec2 new_location)
{
	if (has_parent())
	{
		glm::vec2 parent_loc = get_parent().calcuate_absolute_location();
		
		new_location -= parent_loc;
		
		new_location /= get_parent().calcuate_absolute_scale();
		set_relative_location(glm::rotate(new_location, glm::radians(get_parent().calcuate_absolute_rotation() + 180.f)));
	}
	else
	{
		set_relative_location(new_location);
	}
}
void actor::set_absolute_rotation(float new_rotation)
{
	set_relative_rotation(new_rotation - (has_parent() ? get_parent().calcuate_absolute_rotation() : 0.f));

}


}  // namespace ge
