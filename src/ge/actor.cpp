#include "ge/actor.hpp"

namespace ge {
	
	actor::~actor() {
		if (has_parent()) {
			get_parent()->m_children.erase(shared_from_this());
		}
	}
	
	
	
}
