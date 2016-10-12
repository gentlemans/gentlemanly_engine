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
PUBLIC
	include/
)

if(NOT EMSCRIPTEN)
	target_include_directories(gentlemanly_engine_audio_subsystem
	PRIVATE
		../../deps/vorbis/include
		../../deps/ogg/include
		${OPENAL_INCLUDE_DIR}
	)
	target_link_libraries(gentlemanly_engine_audio_subsystem
	PRIVATE
		${OPENAL_LIBRARY}
		vorbisfile
		vorbisenc
		vorbis
	)
endif()

target_link_libraries(gentlemanly_engine_audio_subsystem
PUBLIC
	gentlemanly_engine
)

if(EMSCRIPTEN)
	set_target_properties(gentlemanly_engine_audio_subsystem PROPERTIES COMPILE_FLAGS "-s USE_OGG=1;-s USE_VORBIS=1")
endif()

