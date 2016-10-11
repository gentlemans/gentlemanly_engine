add_executable(rocket main.cpp)

target_link_libraries(rocket
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)

if(EMSCRIPTEN)
	set_target_properties(rocket PROPERTIES  LINK_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/..@/ -s" SUFFIX ".html")
endif()
