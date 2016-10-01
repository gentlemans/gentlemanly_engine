set(GE_AUDIO_PRIVATE_FILES
	src/audio_subsystem.cpp
	src/sound_asset.cpp
	src/sound.cpp
	src/sound_actor.cpp
)

set(GE_AUDIO_PUBLIC_FILES
	include/ge/audio_subsystem.hpp
	include/ge/sound_actor.hpp
	include/ge/sound_asset.hpp
	include/ge/sound.hpp
)

add_library(gentlemanly_engine_audio_subsystem ${GE_AUDIO_PUBLIC_FILES} ${GE_AUDIO_PRIVATE_FILES})

target_include_directories(gentlemanly_engine_audio_subsystem
PRIVATE
	${OPENAL_INCLUDE_DIR}
	../../deps/vorbis/include
	../../deps/ogg/include
PUBLIC
	include/
)

target_link_libraries(gentlemanly_engine_audio_subsystem
PUBLIC
	gentlemanly_engine
PRIVATE
	vorbis
	vorbisenc
	vorbisfile
	${OPENAL_LIBRARY}
)

