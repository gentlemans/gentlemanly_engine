#include "ge/sound_actor.hpp"
#include "ge/sound_asset.hpp"

#include <AL/al.h>

using namespace ge;

void sound_actor::initialize(std::shared_ptr<sound> sound)
{
	m_sound = std::move(sound);

	alGenSources(1, &m_source_name);
	alSourcei(m_source_name, AL_BUFFER, m_sound->m_buffer_name);
	
	while(true) {
		int state;
		alGetSourcei(m_source_name, AL_SOURCE_STATE, &state);
	}
}

void sound_actor::initialize(const char* assetname) {
	initialize(m_runtime->m_asset_manager.get_asset<sound_asset>(assetname));
}

void sound_actor::play()
{
	alSourcePlay(m_source_name);
}

void sound_actor::pause()
{
	alSourcePause(m_source_name);
}

void sound_actor::rewind()
{
	alSourceRewind(m_source_name);
}



sound_actor::~sound_actor() { alDeleteSources(1, &m_source_name); }
