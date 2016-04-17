#pragma once

#include <glm/glm.hpp>

#include <boost/container/flat_set.hpp>

namespace ge
{
class world;

class actor
{
	actor* m_parent = nullptr;

	boost::container::flat_set<actor*> m_children;

	world* m_world;
	
	size_t m_id_in_world;

public:
	actor(world& world, actor* parent);

	// no move or copy
	actor(const actor&) = delete;
	actor(actor&&) = delete;

	actor& operator=(const actor&) = delete;
	actor& operator=(actor&&) = delete;

	virtual ~actor();

	glm::vec2 relative_location = {0.f, 0.f};
	float relative_rotation = 0.f;
	glm::vec2 relative_scale = {1.f, 1.f};

	glm::vec2 calcuate_absolute_location() const;
	float calcuate_absolute_rotation() const;
	glm::vec2 calcuate_absolute_scale() const;

	glm::mat3 calculate_model_matrix() const;

	void set_parent(actor* new_parent)
	{
		new_parent->m_children.insert(this);
		m_parent = new_parent;
	}

	world& get_world() const { return *m_world; }
	actor* get_parent() const { return m_parent; }
	virtual void render(const glm::mat3& view_projection_matrix) {}
};

}  // namespace ge
