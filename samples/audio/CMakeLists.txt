
add_executable(audio main.cpp)
target_link_libraries(audio
	gentlemanly_engine
	gentlemanly_engine_audio_subsystem
	gentlemanly_engine_renderer
)

GEEmscriptenTarget(audio TRUE ${CMAKE_CURRENT_SOURCE_DIR}../data@/data)
