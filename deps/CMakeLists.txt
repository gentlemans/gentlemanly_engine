cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

if(UNIX)
	set(CMAKE_C_COMPILE_FLAGS "${CMAKE_C_COMPILE_FLAGS} -fPIC")
	set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_COMPILE_FLAGS} -fPIC")
endif()

if(LEVEL STREQUAL 1)
	add_subdirectory(ogg)
	add_subdirectory(boost)
	add_subdirectory(freetype2)
	add_subdirectory(openal-soft)

	set(VIDEO_WAYLAND OFF CACHE BOOL "")
	add_subdirectory(sdl2)
else()
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH};${CMAKE_INSTALL_PREFIX})
	add_subdirectory(vorbis)
	add_subdirectory(libRocket/Build)
endif()
