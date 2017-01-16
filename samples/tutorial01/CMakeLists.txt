
ge_create_exe(tutorial01 "main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../data@data")

target_link_libraries(tutorial01 
	gentlemanly_engine 
	gentlemanly_engine_renderer
)

