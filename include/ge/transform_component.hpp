#pragma once

#include <entityx/Entity.h>

#include <glm/gtx/rotate_vector.hpp>
#include <Box2D/Box2D.h>

#include "ge/transform.hpp"

#include <boost/optional.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace ge
{
struct transform_component
{
	b2Body* m_b2_body = nullptr;
	entityx::Entity m_parent;

	transform_component(transform arg_transform = {}, bool arg_simulate_physics = false)
		: m_transform{arg_transform}, m_simulate_physics{arg_simulate_physics}
	{
	}

	transform get_relative_transform() const { return m_transform; }
	void set_relative_transform(transform new_trans)
	{
		if (m_transform != new_trans) m_cache_dirty = true;

		m_transform = new_trans;
	}

	bool get_simulate_physics() const { return m_simulate_physics; }
	void set_simulate_physics(bool new_simulate_physics)
	{
		if (m_simulate_physics != new_simulate_physics) m_cache_dirty = true;

		m_simulate_physics = new_simulate_physics;
	}

	transform calculate_absolute_transform() const
	{
		if (m_parent.valid())
		{
			auto parent_trans = m_parent.component<const transform_component>()
									.get()
									->calculate_absolute_transform();

			auto local_trans = get_relative_transform();

			transform abs_trans;
			abs_trans.location =
				glm::rotate(local_trans.location, glm::radians(parent_trans.rotation)) +
				parent_trans.location;
			abs_trans.rotation = local_trans.rotation + parent_trans.rotation;

			return abs_trans;
		}
		else
		{
			return get_relative_transform();
		}
	}

	glm::mat3 calculate_model_matrix() const
	{
		glm::mat3 this_model;

		this_model = glm::translate(this_model, get_relative_transform().location);
		this_model = glm::rotate(this_model, glm::radians(get_relative_transform().rotation));

		return m_parent.valid()
				   ? this_model *
						 m_parent.component<const transform_component>()->calculate_model_matrix()
				   : this_model;
	}

	void synchronize()
	{
		if (m_cache_dirty)
		{
			m_b2_body->SetTransform(
				{m_transform.location.x, m_transform.location.y}, m_transform.rotation);

			m_b2_body->SetType(
				m_simulate_physics ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody);

			m_cache_dirty = false;

			return;
		}

		auto&& tmp = m_b2_body->GetTransform();
		m_transform = {{tmp.p.x, tmp.p.y}, tmp.q.GetAngle()};

		m_cache_dirty = false;
	}

private:
	transform m_transform;
	bool m_simulate_physics;
	bool m_cache_dirty = true;
};
}
