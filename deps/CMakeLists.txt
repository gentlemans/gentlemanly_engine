cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PAT};${CMAKE_INSTALL_PREFIX})

add_subdirectory(sdl2)
add_subdirectory(ogg)

set(OGG_LIBRARY ogg)
set(OGG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/ogg/include)
add_subdirectory(vorbis)
add_subdirectory(freetype2)
set(FREETYPE2_LIBRARY freetype)
set(FREETYPE2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/freetype2/include)

add_subdirectory(libRocket/Build)

add_subdirectory(openal-soft)
add_subdirectory(boost)
