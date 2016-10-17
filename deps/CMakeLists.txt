cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

if(LEVEL STREQUAL 1)
	add_subdirectory(ogg)
	add_subdirectory(freetype2)
	add_subdirectory(openal-soft)
else()
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PAT};${CMAKE_INSTALL_PREFIX})
	add_subdirectory(libRocket/Build)
	add_subdirectory(vorbis)
	add_subdirectory(sdl2)
endif()
