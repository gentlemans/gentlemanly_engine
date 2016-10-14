add_executable(animation main.cpp)

target_link_libraries(animation gentlemanly_engine gentlemanly_engine_renderer)

GEEmscriptenTarget(animation ON ${CMAKE_CURRENT_SOURCE_DIR}/../data@/data)

