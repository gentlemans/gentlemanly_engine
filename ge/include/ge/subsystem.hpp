#ifndef GE_SUBSYSTEM_HPP
#define GE_SUBSYSTEM_HPP

#pragma once

#include <chrono>

namespace ge
{
struct runtime;

/// The base class for all subsystems. Making a subsystem is very easy.
/// First, declare a class that derives from `ge::subsystem`:
/// ```
/// class my_subsystem : public ge::subsystem {
/// ```
/// Then, you need to define a config class inside it that users will pass configuration arguments
/// to (this can also be an alias):
/// ```
/// 	struct config { bool print; }
/// ```
/// Then you need to define a initialize function that takes in a `config` object and return a bool;
/// true for success false for failure
/// ```
/// 	bool initialize(const config& c) {
/// 		return true; // for success
/// 		return false; // for failure
/// 	}
/// ```
/// That's all the required pieces. Now you can optionally add an update function that gets called
/// each frame with a delta time.
/// It returns a bool; true if the program should continue to run and false if it should exit.
/// ```
/// 	virtual bool update(std::chrono::duration<float> delta) override { ... }
/// ```
/// Or also a shutdown function that is called when the progrma exits. Again, false is for failure
/// and true is for success.
/// ```
/// 	virtual bool shutdown() override {}
/// ```
/// ```
/// }
/// ```
struct subsystem {
	/// Default constructor
	subsystem() = default;

	// No move or copy to avoid errors
	subsystem(const subsystem&) = delete;
	subsystem(subsystem&&) = delete;

	subsystem& operator=(const subsystem&) = delete;
	subsystem& operator=(subsystem&&) = delete;

	/// Virtual destructor
	virtual ~subsystem(){};

	/// Function to override to get a callback each frame with a delta time
	virtual bool update(std::chrono::duration<float> delta) { return true; };
	/// Function to override that is called when the runtime is shut down
	virtual bool shutdown() { return true; };
	/// The owning runtime object
	runtime* m_runtime;
};

}  // ge

#endif  // GE_ASSET_HPP
