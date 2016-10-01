#include "ge/sound.hpp"

#include <AL/al.h>
#include <vorbis/vorbisfile.h>

#include <array>
#include <exception>
#include <string>
#include <vector>

using namespace ge;

static constexpr int buffer_size = 32768;

sound::sound(const char* filename)
{
	using namespace std::string_literals;

	alGenBuffers(1, &m_buffer_name);

	OggVorbis_File oggfile;

	FILE* file = fopen(filename, "rb");

	if (!file) {
		throw std::runtime_error("Error opening file: "s + filename);
	}

	// the SDK now owns the FILE* object
	ov_open(file, &oggfile, NULL, 0);

	vorbis_info* vInfo = ov_info(&oggfile, -1);

	unsigned int format;

	if (vInfo->channels == 1) {
		format = AL_FORMAT_MONO16;
	} else {
		format = AL_FORMAT_STEREO16;
	}
	size_t freq = vInfo->rate;

	std::array<char, buffer_size> buffer;

	int endianness;
	// find out endianness
	int num = 1;
	if (*(char*)&num == 1) {
		endianness = 0;
	} else {
		endianness = 1;
	}

	std::vector<char> fulldata;

	int bitstream;

	long bytes;
	do {
		bytes = ov_read(&oggfile, buffer.data(), buffer_size, endianness, 2, 1, &bitstream);

		fulldata.insert(fulldata.end(), buffer.begin(), buffer.end());
	} while (bytes > 0);

	ov_clear(&oggfile);

	alBufferData(m_buffer_name, format, fulldata.data(), fulldata.size(), freq);
}
sound::~sound() { alDeleteBuffers(1, &m_buffer_name); }
