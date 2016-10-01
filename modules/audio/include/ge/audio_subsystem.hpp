#ifndef GE_AUDIO_SUBSYSTEM_HPP
#define GE_AUDIO_SUBSYSTEM_HPP

#pragma once

#include "ge/subsystem.hpp"

#include <memory>

namespace ge
{
struct audio_subsystem : subsystem {
	struct config {
	};

	~audio_subsystem();

	bool initialize(config);

	virtual bool update(std::chrono::duration<float> tick) override;
	virtual bool shutdown() override;

	struct pimpl;
	std::unique_ptr<pimpl> m_pimpl;
};
}

#endif  // GE_AUDIO_SUBSYSTEM_HPP
