#ifndef GE_AUDIO_SUBSYSTEM_HPP
#define GE_AUDIO_SUBSYSTEM_HPP

#pragma once

#include "ge/subsystem.hpp"

#include <memory>

namespace ge
{
/// The subsystem for OpenAL. Use this to use sound_actor objects etc.
struct audio_subsystem : subsystem {

	/// No required config
	struct config {
	};

	/// Constructor
	audio_subsystem();

	/// Destructor
	~audio_subsystem();

	/// Init function
	bool initialize(config);

	/// Update func
	virtual bool update(std::chrono::duration<float> tick) override;

	/// Shutdown func
	virtual bool shutdown() override;

private:
	struct pimpl;
	std::unique_ptr<pimpl> m_pimpl;
};
}

#endif  // GE_AUDIO_SUBSYSTEM_HPP
