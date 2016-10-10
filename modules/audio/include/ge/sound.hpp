#ifndef GE_SOUND_HPP
#define GE_SOUND_HPP

#pragma once

#include <chrono>

namespace ge
{
/// Represents a sound buffer in OpenAL`
struct sound {
	/// Constructor
	/// \param file The OGG file to read from
	sound(const char* file);

	/// Destructor
	~sound();

	// No move or copy, this will be a shared_ptr
	sound(const sound&) = delete;
	sound(sound&&) = delete;

	sound& operator=(const sound&) = delete;
	sound& operator=(sound&&) = delete;

	/// The OpenAL buffer name
	unsigned int m_buffer_name = ~0;

	/// How many channels it holds
	uint8_t m_channels;

	operator bool() const { return m_buffer_name != ~0; }
};
}

#endif  // GE_SOUND_HPP
