#include "ge/actor.hpp"

namespace ge
{
actor::~actor()
{
	// clear our children's memories of us
	for (auto child : m_children) {
		child->m_parent = nullptr;
	}

	if (has_parent()) {
		get_parent()->m_children.erase(shared_from_this());
	}
}

glm::mat3 actor::calculate_model_matrix() const noexcept
{
    glm::mat3 this_model;

    this_model *= glm::translate(glm::mat3{}, get_relative_location());
    this_model *= glm::scale(glm::mat3{}, get_relative_scale());
    this_model *= glm::rotate(glm::mat3{}, get_relative_rotation());

    return has_parent() ? get_parent()->calculate_model_matrix() * this_model : this_model;
}

void actor::set_parent(actor *new_parent) noexcept
{
    auto old_parent = get_parent();

    m_parent = new_parent;

    if(new_parent != nullptr) {
        new_parent->m_children.insert(shared_from_this());
    }

    // unparent from old parent
    if (old_parent != nullptr) {
        old_parent->m_children.erase(shared_from_this());
    }

}
}
