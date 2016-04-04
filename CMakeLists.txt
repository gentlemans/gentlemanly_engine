cmake_minimum_required(VERSION 2.6)
project(gentlemanly_engine)

# update the module path so cmake can find libraries that don't have built in CMake support
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# find packages
find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)
find_package(glm REQUIRED)

set(GE_PRIVATE_FILES
	src/window.cpp
)

set(GE_PUBLIC_FILES 
	include/gentlemanly_engine/window.hpp
)


add_library(gentlemanly_engine SHARED ${GE_PRIVATE_FILES} ${GE_PUBLIC_FILES})

target_include_directories(gentlemanly_engine 
PRIVATE 
	include
INTERFACE 
	${CMAKE_INSTALL_PREFIX}/include
PUBLIC 
	${SDL2_INCLUDE_DIR}
	${Boost_INCLUDE_DIR}
)

target_link_libraries(gentlemanly_engine
PRIVATE 
	${SDL2_LIBRARY}
)

target_compile_features(gentlemanly_engine
PUBLIC
	cxx_aggregate_default_initializers
)

# so other people can use it
install(TARGETS gentlemanly_engine DESTINATION lib EXPORT gentlemanly_engine-targets)
install(EXPORT gentlemanly_engine-targets DESTINATION lib/gentlemanly_engine)
install(FILES ${GE_PUBLIC_FILES} DESTINATION include/)
