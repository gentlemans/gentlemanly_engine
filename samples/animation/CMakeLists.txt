ge_create_exe(animation "main.cpp" ${CMAKE_CURRENT_SOURCE_DIR}/../data@/data)

target_link_libraries(animation 
	gentlemanly_engine 
	gentlemanly_engine_renderer
)


