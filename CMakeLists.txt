cmake_minimum_required(VERSION 2.6)
project(gentlemanly_engine)

# update the module path so cmake can find libraries that don't have built in CMake support
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# find packages
find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(GE_PRIVATE_FILES
	src/application.cpp
	src/window_backend/sdl_window.cpp
	src/window_backend/qt_window.cpp
	src/window_backend/qt.cpp
)

set(GE_PUBLIC_FILES 
	include/ge/concept/variadic_concept.hpp
	include/ge/concept/viewport.hpp
	include/ge/concept/window.hpp
	include/ge/concept/window_backend.hpp
	
	include/ge/window_backend/qt.hpp
	include/ge/window_backend/qt_window.hpp
	include/ge/window_backend/qt_viewport.hpp
	
	include/ge/window_backend/sdl.hpp
	include/ge/window_backend/sdl_window.hpp
	include/ge/window_backend/sdl_viewport.hpp
	
	include/ge/application.hpp
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
	Qt5::Widgets
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
install(DIRECTORY include/ge DESTINATION include)
install(FILES cmake/gentlemanly_engine-config.cmake DESTINATION lib/gentlemanly_engine)
