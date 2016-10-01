
add_executable(audio main.cpp)
target_link_libraries(audio
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_audio_subsystem
)
