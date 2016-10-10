#include "ge/sound.hpp"
#include "ge/log.hpp"

#include <AL/al.h>
#include <vorbis/vorbisfile.h>

#include <array>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace ge;

constexpr static size_t buffer_size = 32768;

sound::sound(const char* filename)
{
	using namespace std::string_literals;

	FILE* file = fopen(filename, "rb");

	if (!file) {
		log->error("Error opening file while opening sound: "s + filename);
		return;
	}

	OggVorbis_File oggfile;

	// the SDK now owns the FILE* object
	if (ov_open(file, &oggfile, NULL, 0)) {
		log->error("Error opening OGG file: "s + filename + " for decoding");
		return;
	}

	vorbis_info* vInfo = ov_info(&oggfile, -1);

	ALenum format;

	if (vInfo->channels == 1) {
		format = AL_FORMAT_MONO16;
	} else {
		format = AL_FORMAT_STEREO16;
	}
	ALsizei freq = vInfo->rate;

	std::array<char, buffer_size> tmpbuffer;

	// find out endianness
	int endianness = 0;

	std::vector<char> fulldata;

	int bitstream;

	long bytes;
	do {
		bytes = ov_read(&oggfile, tmpbuffer.data(), buffer_size, endianness, 2, 1, &bitstream);

		if (bytes < 0) {
			ov_clear(&oggfile);
			log->error("Error decoding OGG file: "s + filename);
			return;
		}

		fulldata.insert(fulldata.end(), tmpbuffer.begin(), tmpbuffer.begin() + bytes);
	} while (bytes > 0);

	ov_clear(&oggfile);

	alGenBuffers(1, &m_buffer_name);
	alBufferData(m_buffer_name, format, fulldata.data(), fulldata.size(), freq);
}
sound::~sound() { alDeleteBuffers(1, &m_buffer_name); }
