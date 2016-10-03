#ifndef GE_ANIMATION_ACTOR_HPP
#define GE_ANIMATION_ACTOR_HPP

#pragma once

#include "ge/mesh_actor.hpp"

namespace ge {
	
	class animation_actor : mesh_actor {
		
		void initialize(const std::shared_ptr<mesh_settings>& mes, float fps) {
			
			mesh_actor::initialize(mes);
			
		}
		void initialize(const char* asset_path, float fps) {
			
			mesh_actor::initialize(asset_path);
			
			
			
		}
		
	};
	
}


#endif // GE_ANIMATION_ACTOR_HPP
