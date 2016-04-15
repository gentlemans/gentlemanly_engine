#pragma once

#include <tuple>
// for shared_ptr
#include <memory>

// for for_each and find
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/fusion/algorithm.hpp>

#include <boost/signals2.hpp>

#include "ge/concept/window_backend.hpp"
#include "ge/asset_manager.hpp"

namespace ge
{
// the window backend to use
template <typename _window_backend>
class application
{
	// check concepts
	BOOST_CONCEPT_ASSERT((concept::WindowBackend<_window_backend>));

public:
	application(int& argc, char** argv) : window_backend(*this, argc, argv) {}
	// move only
	application(const application&) = delete;
	application(application&&) = default;

	application& operator=(const application&) = delete;
	application& operator=(application&&) = default;

	// destructor
	~application() = default;

	void execute() { window_backend.execute(); }
	boost::signals2::signal<void()> update;
	boost::signals2::signal<void()> init;

	_window_backend window_backend;
	ge::asset_manager asset_manager;
};

}  // namespace ge
