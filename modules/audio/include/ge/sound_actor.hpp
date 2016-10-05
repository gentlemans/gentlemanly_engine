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

	/// Get the current sound object
	/// \return The sound object
	const std::shared_ptr<sound>& get_sound() const { return m_sound; }
	/// Set the sound object to use
	/// \param new_sound The new sound
	void set_sound(std::shared_ptr<sound> new_sound);

	/// Plays the sound at the current location
	void play();

	/// Pauses the sound, keeping the position
	void pause();

	/// Rewinds the sound to the beginning
	void rewind();

	/// Querys if the sound is playing
	/// \return If the sound is playing
	bool is_playing() const;

	/// The OpenAL source name
	unsigned int m_source_name;

	void tick(std::chrono::duration<float> delta);
	
private:
	/// The sound object to play
	std::shared_ptr<sound> m_sound;
};
}

#endif  // GE_SOUND_SOURCE_HPP
