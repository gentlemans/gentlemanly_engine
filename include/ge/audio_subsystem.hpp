#ifndef GE_AUDIO_SUBSYSTEM_HPP
#define GE_AUDIO_SUBSYSTEM_HPP

#pragma once

#include "ge/subsystem.hpp"

struct ALCdevice;
struct ALCcontext;

namespace ge {

struct audio_subsystem : subsystem{
	
	struct config{};
	
	bool initialize(config);
	
	virtual bool update(std::chrono::duration<float> tick) override;
	virtual bool shutdown() override;
	
	ALCDevice* m_device;
	ALCcontext* m_context;
};

}

#endif // GE_AUDIO_SUBSYSTEM_HPP
