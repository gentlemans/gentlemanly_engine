#ifndef GE_RUNTIME_HPP
#define GE_RUNTIME_HPP

#pragma once

#include "ge/concept/subsystem.hpp"
#include "ge/hash_typeindex.hpp"

#include <unordered_map>
#include <memory>

#include <boost/type_index.hpp>
#include <boost/concept/requires.hpp>

// we use this so it has a default constructor--unique_ptr disallows a nullptr deleter 
// and apparently operator[] of std::unordered_map requires a default constructor
struct deleter {
	void(*delptr)(void*) = nullptr;
	
	void operator()(void* todel) const {
		delptr(todel);
	}
	
};

namespace ge {

struct runtime {
	
	template<typename Subsystem>
	BOOST_CONCEPT_REQUIRES(
		((ge::concept::Subsystem<Subsystem>)),
		(void))
	add_subsystem(const typename Subsystem::config& config) {
		
		using boost::typeindex::type_id;
		
		// see if there is already one
		if(m_subsystems.find(type_id<Subsystem>()) != m_subsystems.end()) {
			// we aren't interseted in adding another one
			return;
		}
		
		// add it!
		m_subsystems[type_id<Subsystem>()] = std::unique_ptr<Subsystem, deleter>(new Subsystem{}, {[](void* todel) {
			Subsystem* casted = (Subsystem*)todel;
			delete casted;
		}});
	}
	
	template<typename Subsystem>
	BOOST_CONCEPT_REQUIRES(
		((ge::concept::Subsystem<Subsystem>)),
		(Subsystem*))
	get_subsystem() {
		
		using boost::typeindex::type_id;
		
		if(auto iter = m_subsystems.find(type_id<Subsystem>()) != m_subsystems.end()) {
			return static_cast<Subsystem>(iter.second.get());
		}
		
		return nullptr;

	}
	
	void tick() {
		
	}
	
private:
	
	std::unordered_map<boost::typeindex::type_index, std::unique_ptr<void, deleter>> m_subsystems;
	
};

}

#endif // GE_RUNTIME_HPP
