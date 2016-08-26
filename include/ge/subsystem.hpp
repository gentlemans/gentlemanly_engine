#pragma once

#include <boost/concept/assert.hpp>

#include <ge/concept/application.hpp>

namespace ge {

/// \brief A class for building subsystems.
/// In order to build a subsystem, define the functions:
/// bool initialize()
/// bool exit()
/// void update()
template<typename ApplicationType, typename Derived>
class subsystem {
	
	// Make sure that it is actually an application type
	BOOST_CONCEPT_ASSERT((concept::Application<ApplicationType>));
	
public:
	
	subsystem(ApplicationType& app) {
		app.signal_init.connect([this]{
			static_cast<Derived>(this).initialize();
		});
		app.signal_update.connect([this]{
			static_cast<Derived>(this).update();
		});
		app.signal_quit.connect([this]{
			static_cast<Derived>(this).exit();
		});
	}
	
	
	ApplicationType* app;
	
};

} // namespace ge
