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


# find packages
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(SDL2 REQUIRED)

add_definitions(-DBOOST_ALL_NO_LIB)

# These are optional, we can use the packaged if we can to avoid buliding it
if(UNIX)
	find_package(Freetype)
endif()
#find_package(assimp)

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

set(GE_PRIVATE_FILES
	src/ge/actor.cpp
	src/ge/rocket_subsystem.cpp
	src/ge/lodepng.cpp
	src/ge/material.cpp
	src/ge/material_asset.cpp
	src/ge/mesh.cpp
	src/ge/mesh_actor.cpp
	src/ge/mesh_asset.cpp
	src/ge/sdl_subsystem.cpp
	src/ge/shader.cpp
	src/ge/shader_asset.cpp
	src/ge/texture.cpp
	src/ge/texture_asset.cpp
	src/ge/ui/render_interface.cpp
	src/ge/mesh_settings.cpp
	src/ge/ui/rocket_document_asset.cpp
	src/ge/ui/rocket_input_consumer.cpp
)

set(GE_PUBLIC_FILES
	include/external/glext.h
	include/external/wglext.h
	include/ge/actor.hpp
	include/ge/asset_manager.hpp
	include/ge/camera_actor.hpp
	include/ge/concept/asset.hpp
	include/ge/gl.hpp
	include/ge/hash_typeindex.hpp
	include/ge/input_event.hpp
	include/ge/json.hpp
	include/ge/json_helper.hpp
	include/ge/lodepng.h
	include/ge/material.hpp
	include/ge/material_asset.hpp
	include/ge/mesh.hpp
	include/ge/mesh_actor.hpp
	include/ge/mesh_asset.hpp
	include/ge/ortho2d.hpp
	include/ge/runtime.hpp
	include/ge/sdl_subsystem.hpp
	include/ge/shader.hpp
	include/ge/shader_asset.hpp
	include/ge/subsystem.hpp
	include/ge/texture.hpp
	include/ge/texture_asset.hpp
	include/ge/input_subsystem.hpp
	include/ge/timer_manager.hpp
	include/ge/transform.hpp
	include/ge/ui/render_interface.hpp
	include/ge/ui/rocket_document_asset.hpp
	include/ge/ui/rocket_font_asset.hpp
	include/ge/ui/rocket_input_consumer.hpp
	include/ge/ui/system_interface.hpp

)



add_library(gentlemanly_engine SHARED ${GE_PRIVATE_FILES} ${GE_PUBLIC_FILES})


target_include_directories(gentlemanly_engine 
PRIVATE 
	${OPENGL_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
	deps/assimp/include
	deps/openal-soft/include
PUBLIC
	include
	deps/glm/
	${Boost_INCLUDE_DIR}
	deps/libRocket/Include/
	deps/openal-soft/include
)

if(WIN32)
    target_include_directories(gentlemanly_engine
    PRIVATE
        deps/glew_win32/include
    )
	target_link_libraries(gentlemanly_engine
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/deps/glew_win32/lib/Release/x64/glew32.lib
		OpenAL32
	)
else()
	target_link_libraries(gentlemanly_engine
		PRIVATE
		openal
	)
endif()

target_link_libraries(gentlemanly_engine
PRIVATE 
	${SDL2_LIBRARY}
	${OPENGL_LIBRARIES}
PUBLIC
	RocketCore
	RocketDebugger
	RocketControls
	Threads::Threads
	
)

target_link_libraries(gentlemanly_engine
PUBLIC 
	debug ${Boost_FILESYSTEM_LIBRARY_DEBUG}
	optimized ${Boost_FILESYSTEM_LIBRARY_RELEASE}
	debug ${Boost_SYSTEM_LIBRARY_DEBUG}
	optimized ${Boost_SYSTEM_LIBRARY_RELEASE}
)

target_link_libraries(gentlemanly_engine
PRIVATE
	assimp
)


target_compile_features(gentlemanly_engine
PUBLIC
	cxx_generic_lambdas
	cxx_variadic_templates
)

# so other people can use it
install(DIRECTORY include/ge DESTINATION include)
install(FILES cmake/gentlemanly_engine-config.cmake cmake/modules/FindEntityX.cmake DESTINATION lib/gentlemanly_engine)

# Samples

if(GE_BUILD_SAMPLES)
	add_subdirectory(samples)
endif()

