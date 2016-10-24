
ge_create_exe(audio "main.cpp" ${CMAKE_CURRENT_SOURCE_DIR}/../data@/data)

target_link_libraries(audio
	gentlemanly_engine
	gentlemanly_engine_audio_subsystem
	gentlemanly_engine_renderer
)

