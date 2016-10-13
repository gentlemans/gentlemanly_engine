add_executable(rocket main.cpp)

target_link_libraries(rocket
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)

GEEmscriptenTarget(rocket TRUE "${CMAKE_CURRENT_SOURCE_DIR}/../data@/data")
