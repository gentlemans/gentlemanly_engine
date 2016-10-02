#ifndef GE_SOUND_SOURCE_HPP
#define GE_SOUND_SOURCE_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/sound.hpp"

#include <memory>

namespace ge
{

/// Actor that plays a sound at it's location. 
struct sound_actor : actor {

	/// Init function from a sound
	/// \param sound The sound object to play
	void initialize(std::shared_ptr<sound> sound);

	/// Init function from an asset
	/// \param assetname Asset path to a sound asset
	void initialize(const char* assetname);

	/// Destructor
	~sound_actor();

	/// Plays the sound at the current location
	void play();

	/// Pauses the sound, keeping the position
	void pause();

	/// Rewinds the sound to the beginning
	void rewind();

	/// Querys if the sound is playing
	/// \return If the sound is playing
	bool is_playing() const;

	std::shared_ptr<sound> m_sound;

	unsigned int m_source_name;
};
}

#endif  // GE_SOUND_SOURCE_HPP
