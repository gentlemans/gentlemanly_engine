
add_executable(audio main.cpp)
target_link_libraries(audio
	gentlemanly_engine
	gentlemanly_engine_audio_subsystem
	gentlemanly_engine_renderer
)
if(EMSCRIPTEN)
	set_target_properties(audio PROPERTIES  LINK_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/..@/ -s" SUFFIX ".html" COMPILE_FLAGS "-g3 --minify 0")
endif()
