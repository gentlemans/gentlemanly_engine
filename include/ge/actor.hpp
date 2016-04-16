#pragma once

#include <glm/glm.hpp>

#include <unordered_set>

namespace ge
{
class actor
{
	actor* parent = nullptr;

	std::unordered_set<actor*> children;

public:
	actor(actor* parent);

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
		new_parent->children.insert(this);
		parent = new_parent;
	}
	const actor* get_parent() const { return parent; };
	actor* get_parent() { return parent; }
	virtual void render(const glm::mat3& view_projection_matrix) {}
	void render_tree(const glm::mat3& view_projection_matrix)
	{
		render(view_projection_matrix);

		for (auto child : children)
		{
			child->render_tree(view_projection_matrix);
		}
	}
};

}  // namespace ge
