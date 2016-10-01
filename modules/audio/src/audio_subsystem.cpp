#include "ge/audio_subsystem.hpp"
#include "ge/runtime.hpp"

using namespace ge;

#include <AL/al.h>
#include <AL/alc.h>

#include <string>

#include <boost/lexical_cast.hpp>

struct audio_subsystem::pimpl {
	ALCdevice* device;
	ALCcontext* context;
};

audio_subsystem::audio_subsystem() = default;
audio_subsystem::~audio_subsystem() = default;

bool audio_subsystem::initialize(audio_subsystem::config)
{
	m_pimpl = std::make_unique<pimpl>();
	
	const char * devicename = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
	std::cout << devicename;
	m_pimpl->device = alcOpenDevice(devicename);
	if (!m_pimpl->device) {
		m_runtime->m_log->error("Failed to open OpenAL device.");
	}

	m_pimpl->context = alcCreateContext(m_pimpl->device, nullptr);
	alcMakeContextCurrent(m_pimpl->context);

	if (!m_pimpl->context) {
		m_runtime->m_log->error("Failed to create OpenAL context. Error: " +
								boost::lexical_cast<std::string>(alcGetError(m_pimpl->device)));
	}
	return true;
}

bool audio_subsystem::update(std::chrono::duration<float> tick) { return true; }
bool audio_subsystem::shutdown() { alcCloseDevice(m_pimpl->device); alcDestroyContext(m_pimpl->context);  }
