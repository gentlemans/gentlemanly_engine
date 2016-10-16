cmake_minimum_required(VERSION 3.0)

project(gentlemanly_engine)

set(PROJECT_VERSION 0.1.0)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

option(GE_BUILD_SAMPLES "Should the samples be built?" ON)

# update the module path so cmake can find libraries that don't have built in CMake support
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/install;${CMAKE_PREFIX_PATH})

include(cmake/emscripten.cmake)

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

# Compile Dependencies
if(NOT EMSCRIPTEN)
	if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/build)
		message("Compiling dependencies for the first time, this might take a while but only happens once, ${CMAKE_COMMAND} .. -G\"${CMAKE_GENERATOR}\"")
		execute_process( COMMAND mkdir build WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps)
		execute_process(
			COMMAND cmake .. -G "Unix Makefiles"
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/build
			RESULT_VARIABLE CONFIG_SUCCESS
		)
		if(NOT CONIFG_SUCCESS)
			message(error, "Failed to configure dependencies. :(")
		endif()
		message("Dependencies configured, compiling")
		execute_process(
			COMMAND ${CMAKE_COMMAND} --build . --target install
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/build
		)
	else()
		message("Dependencies already compiled, delete deps/build to recompile")
	endif()
endif()

if (EMSCRIPTEN)
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc" CACHE STRING "")
    set(CMAKE_C_CREATE_STATIC_LIBRARY "emcc -o <TARGET> <LINK_FLAGS> <OBJECTS>" CACHE STRING "")
    set(CMAKE_CXX_CREATE_STATIC_LIBRARY "emcc -o <TARGET> <LINK_FLAGS> <OBJECTS>" CACHE STRING "")
endif()

# LIBROCKET -- only for emscripten
if(EMSCRIPTEN)
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
	set(BUILD_SAMPLES OFF CACHE BOOL "")
	add_subdirectory(deps/libRocket/Build)
	set_target_properties(RocketCore PROPERTIES COMPILE_FLAGS "-s USE_FREETYPE=1")
endif()

add_subdirectory(ge)
add_subdirectory(modules)

# Samples

if(GE_BUILD_SAMPLES)
	add_subdirectory(samples)
endif()
