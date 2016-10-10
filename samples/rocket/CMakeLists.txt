add_executable(rocket main.cpp)

target_link_libraries(rocket
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)

if(EMSCRIPTEN)
	set_target_properties(rocket PROPERTIES  LINK_FLAGS "-s DISABLE_EXCEPTION_CATCHING=0 -s USE_SDL=2 -s FULL_ES3=1 --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/..@/ -s" SUFFIX ".html" COMPILE_FLAGS "-g3 --minify 0")
endif()
