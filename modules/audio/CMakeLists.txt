set(GE_AUDIO_PRIVATE_FILES
	src/audio_subsystem.cpp
)

set(GE_AUDIO_PUBLIC_FILES
	include/ge/audio_subsystem.hpp
)

add_library(gentlemanly_engine_audio_subsystem ${GE_AUDIO_PUBLIC_FILES} ${GE_AUDIO_PRIVATE_FILES})

target_include_directories(gentlemanly_engine_audio_subsystem
PRIVATE
	../../deps/openal-soft/include
PUBLIC
	include/
)

target_link_libraries(gentlemanly_engine_audio_subsystem
PUBLIC
	gentlemanly_engine
)

if(WIN32)

	target_link_libraries(gentlemanly_engine_audio_subsystem
	PUBLIC
		OpenAL32
	)
else()
	target_link_libraries(gentlemanly_engine_audio_subsystem
	PUBLIC
		openal
	)
endif()
