
#ifndef GE_SUBSYSTEM_HPP
#define GE_SUBSYSTEM_HPP

#pragma once

#include <boost/concept_check.hpp>


namespace ge
{

namespace concept
{
/// A concpet defining what an asset class looks like.
template <typename X>
struct Subsystem {

	using config = typename X::config;
	
	BOOST_CONCEPT_USAGE(Subsystem) { 
		
		// default constructor
		X c = X();
		
		// default constructor for config also
		bool b = c.initialize(config{});
		b = c.update();
		b = c.shutdown();
		
	}
	
private:
};
}
}

#endif // GE_ASSET_HPP
