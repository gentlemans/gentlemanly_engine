#ifndef GE_SOUND_SOURCE_HPP
#define GE_SOUND_SOURCE_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/sound.hpp"

#include <memory>

namespace ge
{
struct sound_actor : actor {
	void initialize(std::shared_ptr<sound> sound);
	void initialize(const char* assetname);
	~sound_actor();
	
	void play();
	void pause();
	void rewind();
	
	bool is_playing() const;

	std::shared_ptr<sound> m_sound;

	unsigned int m_source_name;
};
}

#endif  // GE_SOUND_SOURCE_HPP
