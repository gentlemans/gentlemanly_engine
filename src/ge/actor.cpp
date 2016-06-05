#include "ge/actor.hpp"

namespace ge
{
actor::~actor()
{
	// clear our children's memories of us
	for (auto child : m_children)
	{
		child->m_parent = nullptr;
	}

	if (has_parent())
	{
		get_parent()->m_children.erase(shared_from_this());
	}
}
}
