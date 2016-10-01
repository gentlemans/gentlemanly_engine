#ifndef GE_SOUND_HPP
#define GE_SOUND_HPP

#pragma once

namespace ge
{
struct sound {
	sound(const char* file);

	~sound();

	sound(const sound&) = delete;
	sound(sound&&) = delete;

	sound& operator=(const sound&) = delete;
	sound& operator=(sound&&) = delete;

	unsigned int m_buffer_name;
};
}

#endif  // GE_SOUND_HPP
