#include "ge/audio_subsystem.hpp"
#include "ge/runtime.hpp"

using namespace ge;

#include <AL/al.h>
#include <AL/alc.h>

#include <string>

#include <boost/lexical_cast.hpp>

bool audio_subsystem::initialize(audio_subsystem::config) {
	
	m_device = alcOpenDevice(nullptr);
	if(!m_device) {
		m_runtime->m_log->error("Failed to open OpenAL device.");
	}
	
	m_context = alcCreateContext(m_device, nullptr);
	alcMakeContextCurrent(m_context);
	
	if(!m_context) {
		m_runtime->m_log->error("Failed to create OpenAL context. Error: " +
			boost::lexical_cast<std::string>(alcGetError(m_device)));
	}
}

bool audio_subsystem::update(std::chrono::duration<float> tick)
{
	
}
bool audio_subsystem::shutdown()
{
}


