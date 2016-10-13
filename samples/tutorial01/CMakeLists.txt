
add_executable(tutorial01 main.cpp)

target_link_libraries(tutorial01 gentlemanly_engine gentlemanly_engine_renderer)

GEEmscriptenTarget(tutorial01 TRUE ${CMAKE_CURRENT_SOURCE_DIR}/../data@data)
