#pragma once

#include <glm/glm.hpp>

#include <boost/container/flat_set.hpp>

#include <boost/signals2.hpp>

#include <Box2D/Box2D.h>

namespace ge
{
class world;

class actor
{
	actor* m_parent = nullptr;

	boost::container::flat_set<actor*> m_children;

	world* m_world;

	size_t m_id_in_world;

	glm::vec2 m_relative_location = {0.f, 0.f};
	float m_relative_rotation = 0.f;
	glm::vec2 m_relative_scale = {1.f, 1.f};

public:
	actor(world& world, actor* parent);

	// no move or copy
	actor(const actor&) = delete;
	actor(actor&&) = delete;

	actor& operator=(const actor&) = delete;
	actor& operator=(actor&&) = delete;

	virtual ~actor();

	void set_relative_location(glm::vec2 new_location)
	{
		if (new_location != m_relative_location)
		{
			signal_location_changed(*this);
			signal_transform_changed(*this);
		}
		m_relative_location = new_location;
	}
	glm::vec2 get_relative_location() const { return m_relative_location; }
	void set_relative_rotation(float new_rotation)
	{
		if (new_rotation != m_relative_rotation)
		{
			signal_rotation_changed(*this);

			signal_transform_changed(*this);
		}
		m_relative_rotation = new_rotation;
	}
	float get_relative_rotation() const { return m_relative_rotation; }
	void set_relative_scale(glm::vec2 new_scale)
	{
		if (new_scale != m_relative_scale)
		{
			signal_scale_changed(*this);
			signal_transform_changed(*this);
		}
		m_relative_scale = new_scale;
	}
	glm::vec2 get_relative_scale() const { return m_relative_scale; }
	glm::vec2 calcuate_absolute_location() const;
	float calcuate_absolute_rotation() const;
	glm::vec2 calcuate_absolute_scale() const;

	glm::mat3 calculate_model_matrix() const;

	// absolute sets
	void set_absolute_location(glm::vec2 new_location);
	void set_absolute_rotation(float new_rotation);

	void set_parent(actor* new_parent)
	{
		new_parent->m_children.insert(this);
		m_parent = new_parent;
	}
	world& get_world() const { return *m_world; }
	actor& get_parent() const { return *m_parent; }
	bool has_parent() const { return m_parent; }
	virtual void render(const glm::mat3& view_projection_matrix) {}
	// SIGNALS
	boost::signals2::signal<void(actor& actor_that_changed)> signal_location_changed;
	boost::signals2::signal<void(actor& actor_that_changed)> signal_rotation_changed;
	boost::signals2::signal<void(actor& actor_that_changed)> signal_scale_changed;
	boost::signals2::signal<void(actor& actor_that_changed)> signal_transform_changed;
};

}  // namespace ge
