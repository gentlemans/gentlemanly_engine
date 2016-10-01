#include "ge/sound.hpp"

#include <AL/al.h>
#include <vorbis/vorbisfile.h>

#include <array>
#include <exception>
#include <string>
#include <vector>








#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>


#define BUFFER_SIZE     32768       // 32 KB buffers


using namespace std;


// This function loads a .ogg file into a memory buffer and returns
// the format and frequency.
void LoadOGG(const char *fileName, vector<char> &buffer, ALenum &format, ALsizei &freq)
    {
    int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE];                // Local fixed size array
    FILE *f;

    // Open for binary reading
    f = fopen(fileName, "rb");

    if (f == NULL)
        {
        cerr << "Cannot open " << fileName << " for reading..." << endl;
        exit(-1);
        }
    // end if

    vorbis_info *pInfo;
    OggVorbis_File oggFile;

    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0)
        {
        cerr << "Error opening " << fileName << " for decoding..." << endl;
        exit(-1);
        }
    // end if

    // Get some information about the OGG file
    pInfo = ov_info(&oggFile, -1);

    // Check the number of channels... always use 16-bit samples
    if (pInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;
    // end if

    // The frequency of the sampling rate
    freq = pInfo->rate;

    // Keep reading until all is read
    do
        {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0)
            {
            ov_clear(&oggFile);
            cerr << "Error decoding " << fileName << "..." << endl;
            exit(-1);
            }
        // end if

        // Append to end of buffer
        buffer.insert(buffer.end(), array, array + bytes);
        }
    while (bytes > 0);

    // Clean up!
    ov_clear(&oggFile);
    }
// end of LoadOGG


int maindd(const char* file)
    {
    ALint state;                            // The state of the sound source
    ALuint bufferID;                        // The OpenAL sound buffer ID
    ALuint sourceID;                        // The OpenAL sound source
    ALenum format;                          // The sound data format
    ALsizei freq;                           // The frequency of the sound data
    vector<char> bufferData;                // The sound buffer data from file

    // Make sure there is a file name


    // Initialize the OpenAL library
	const char * devicename = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
std::cout << devicename << std::endl << std::endl;
    auto device = alcOpenDevice(devicename);
	auto ctx = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(ctx);

    // Create sound buffer and source
	alGenBuffers(1, &bufferID);

    // Load the OGG file into memory
    LoadOGG(file, bufferData, format, freq);

    // Upload sound data to buffer
    alBufferData(bufferID, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);



	alGenSources(1, &sourceID);
    // Attach sound buffer to source
    alSourcei(sourceID, AL_BUFFER, bufferID);

    // Finally, play the sound!!!
    alSourcePlay(sourceID);

    // This is a busy wait loop but should be good enough for example purpose
    do
        {
        // Query the state of the souce
        alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
        }
    while (state != AL_STOPPED);

    // Clean up sound buffer and source
    alDeleteBuffers(1, &bufferID);
    alDeleteSources(1, &sourceID);

    // Clean up the OpenAL library

    return 0;
    }
// end of main


using namespace ge;

static constexpr int buffer_size = 32768;

sound::sound(const char* filename)
{
	maindd(filename);
	
	using namespace std::string_literals;

	alGenBuffers(1, &m_buffer_name);

	FILE* file = fopen(filename, "rb");

	if (!file) {
		throw std::runtime_error("Error opening file: "s + filename);
	}

	OggVorbis_File oggfile;

	// the SDK now owns the FILE* object
	if(ov_open(file, &oggfile, NULL, 0)) {
		throw std::runtime_error("Error opening OGG file: "s + filename + " for decoding");
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

		if(bytes < 0) {
			ov_clear(&oggfile);
			throw std::runtime_error("Error decoding "s + filename);
		}
		
		
		fulldata.insert(fulldata.end(), tmpbuffer.begin(), tmpbuffer.end());
	} while (bytes > 0);

	ov_clear(&oggfile);

	alBufferData(m_buffer_name, format, fulldata.data(), fulldata.size(), freq);
}
sound::~sound() { alDeleteBuffers(1, &m_buffer_name); }
