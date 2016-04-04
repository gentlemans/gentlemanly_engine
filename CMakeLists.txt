cmake_minimum_required(VERSION 2.6)
project(gentlemanly_engine)

add_executable(gentlemanly_engine main.cpp)

install(TARGETS gentlemanly_engine RUNTIME DESTINATION bin)
