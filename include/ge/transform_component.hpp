#pragma once

#include "ge/transform.hpp"

#include <entityx/Entity.h>

#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace ge
{
struct transform_component
{
	transform_component(transform trans, entityx::Entity parent = {})
		: m_relative_transform{trans}, m_parent{parent}
	{
	}

	transform m_relative_transform;
	entityx::Entity m_parent;

	transform calculate_absolute_transform() const
	{
		if (m_parent.valid())
		{
			auto parent_trans = m_parent.component<const transform_component>()
									.get()
									->calculate_absolute_transform();

			transform abs_trans;
			abs_trans.location =
				glm::rotate(m_relative_transform.location, glm::radians(parent_trans.rotation)) +
				parent_trans.location;
			abs_trans.rotation = m_relative_transform.rotation + parent_trans.rotation;

			return abs_trans;
		}
		else
		{
			return m_relative_transform;
		}
	}

	glm::mat3 calculate_model_matrix() const
	{
		glm::mat3 this_model;

		this_model = glm::translate(this_model, m_relative_transform.location);
		this_model = glm::rotate(this_model, glm::radians(m_relative_transform.rotation));

		return m_parent.valid()
				   ? this_model *
						 m_parent.component<const transform_component>()->calculate_model_matrix()
				   : this_model;
	}
};
}
