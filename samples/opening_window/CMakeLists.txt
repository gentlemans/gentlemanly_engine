cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/")


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(gentlemanly_engine_opening_window main.cpp)

target_link_libraries(gentlemanly_engine_opening_window
	gentlemanly_engine
)




