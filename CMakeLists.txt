cmake_minimum_required(VERSION 2.6)
project(gentlemanly_engine)

# update the module path so cmake can find libraries that don't have built in CMake support
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# find packages
find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

set(GE_PRIVATE_FILES
	src/application.cpp
	src/window.cpp
)

set(GE_PUBLIC_FILES 
	include/gentlemanly_engine/concept/subsystem.hpp
	include/gentlemanly_engine/concept/variadic_concept.hpp
	include/gentlemanly_engine/subsystem/graphics.hpp
	include/gentlemanly_engine/application.hpp
	include/gentlemanly_engine/window.hpp
)


add_library(gentlemanly_engine SHARED ${GE_PRIVATE_FILES} ${GE_PUBLIC_FILES})

target_include_directories(gentlemanly_engine 
PRIVATE 
	include
	${OPENGL_INCLUDE_DIR}
INTERFACE 
	${CMAKE_INSTALL_PREFIX}/include
PUBLIC 
	${SDL2_INCLUDE_DIR}
	${Boost_INCLUDE_DIR}
)

target_link_libraries(gentlemanly_engine
PUBLIC
	${SDL2_LIBRARY}
PRIVATE 
	${OPENGL_LIBRARIES}
)

target_compile_features(gentlemanly_engine
PUBLIC
	cxx_aggregate_default_initializers
	cxx_generic_lambdas
)

# so other people can use it
install(TARGETS gentlemanly_engine DESTINATION lib EXPORT gentlemanly_engine-targets)
install(EXPORT gentlemanly_engine-targets DESTINATION lib/gentlemanly_engine)
install(DIRECTORY include/gentlemanly_engine DESTINATION include)
install(FILES cmake/gentlemanly_engine-config.cmake DESTINATION lib/gentlemanly_engine)
