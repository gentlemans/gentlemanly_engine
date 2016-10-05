cmake_minimum_required(VERSION 2.6)

project(gentlemanly_engine)

set(PROJECT_VERSION 0.1.0)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

option(GE_BUILD_SAMPLES "Should the samples be built?" ON)

# update the module path so cmake can find libraries that don't have built in CMake support
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Doxygen)

if(DOXYGEN_FOUND)

	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)

	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Generating Doxygen documentation..."
		DEPENDS ${GE_PRIVATE_FILES} ${GE_PUBLIC_FILES}
	)

else()
	message("If you want the target \"doc\" to be avaliable to build doxygen documentation,
	then install Doxygen or if it is already installed, set DOXYGEN_EXECUTABLE with a path to doxygen.")
endif()

set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)
add_subdirectory(deps/sdl2)
set(SDL2_LIBRARY SDL2-static CACHE STRING "")
set(SDL2_INCLUDE_DIR deps/sdl2/include CACHE PATH "")

add_subdirectory(deps/ogg)
set(OGG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/deps/ogg CACHE PATH "")
set(OGG_LIBRARIES ogg CACHE STRING "")
set(OGG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/ogg/include CACHE PATH "")

add_subdirectory(deps/vorbis)
add_dependencies(vorbis ogg)

# These are optional, we can use the packaged if we can to avoid buliding it
if(UNIX)
	find_package(Freetype)
endif()

if(UNIX)
	find_package(assimp)
endif()

message("DIR: ${ASSIMP_INCLUDE_DIRS}")

#ASSIMP
if(NOT ASSIMP_INCLUDE_DIRS)

	message("Using submodule version of assimp, building from scratch")

    set(ASSIMP_BUILD_TESTS OFF)
    set(ASSIMP_BUILD_SAMPLES OFF)
    set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
    add_subdirectory(deps/assimp)

endif()

if(NOT FREETYPE_FOUND)

	message("Using submodule version of freetype, building from scratch")

    #FT2

    set(BUILD_SHARED_LIBS OFF)
    add_subdirectory(deps/freetype2)
    set(FREETYPE_LIBRARY freetype CACHE STRING "")
    set(FREETYPE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype2/include)

endif()

# LIBROCKET

set(BUILD_SAMPLES OFF CACHE BOOL "")
add_subdirectory(deps/libRocket/Build)

set(ALSOFT_UTILS OFF CACHE BOOL "")
set(ALSOFT_EXAMPLES OFF CACHE BOOL "")
set(ALSOFT_TESTS OFF CACHE BOOL "")
set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "")

add_subdirectory(deps/openal-soft)

if(WIN32)
	set(OPENAL_LIBRARY OpenAL32)
else()
	set(OPENAL_LIBRARY openal)
endif()

set(OPENAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/openal-soft/include)



add_subdirectory(ge)
add_subdirectory(modules)

# Samples

if(GE_BUILD_SAMPLES)
	add_subdirectory(samples)
endif()
