
ge_create_exe(rocket "main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../data@/data")

target_link_libraries(rocket
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)

