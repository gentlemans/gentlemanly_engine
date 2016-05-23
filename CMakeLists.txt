cmake_minimum_required(VERSION 2.6)

# Allow VERSION in project()
cmake_policy(SET CMP0048 NEW)

project(gentlemanly_engine VERSION 0.1.0)


option(DOXYGEN_EXTRA_FLAGS "Extra flags to be sent to doxygen." "")
option(BUILD_SAMPLES "Should the samples be built?" ON)


# update the module path so cmake can find libraries that don't have built in CMake support
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)


# find packages
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(assimp REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)


set(ENTITYX_BUILD_TESTING OFF)
add_subdirectory(entityx)


set(GE_PRIVATE_FILES
	
	src/ge/asset_manager.cpp
	src/ge/texture.cpp
	src/ge/lodepng.cpp
	src/ge/material_asset.cpp
	src/ge/material.cpp
	src/ge/mesh_asset.cpp
	src/ge/mesh.cpp
	src/ge/model_system.cpp
	src/ge/qt_application.cpp
	src/ge/qt_viewport.cpp
	src/ge/qt_window.cpp
	src/ge/sdl_application.cpp
	src/ge/sdl_viewport.cpp
	src/ge/sdl_window.cpp
	src/ge/shader.cpp

)

set(GE_PUBLIC_FILES 
	include/ge/asset_manager.hpp
	include/ge/camera_component.hpp
	include/ge/concept/application.hpp
	include/ge/concept/asset.hpp
	include/ge/concept/component.hpp
	include/ge/concept/variadic_concept.hpp
	include/ge/concept/viewport.hpp
	include/ge/concept/window.hpp
	include/ge/json.hpp
	include/ge/lodepng.h
	include/ge/material_asset.hpp
	include/ge/material.hpp
	include/ge/mesh_asset.hpp
	include/ge/mesh.hpp
	include/ge/model_component.hpp
	include/ge/model_system.hpp
	include/ge/ortho2d.hpp
	include/ge/qt_application.hpp
	include/ge/qt_viewport.hpp
	include/ge/qt_window.hpp
	include/ge/sdl_application.hpp
	include/ge/sdl_viewport.hpp
	include/ge/sdl_window.hpp
	include/ge/shader_asset.hpp
	include/ge/shader.hpp
	include/ge/texture.hpp
	include/ge/texture_asset.hpp
	include/ge/transform.hpp
	include/ge/velocity_component.hpp
)



add_library(gentlemanly_engine SHARED ${GE_PRIVATE_FILES} ${GE_PUBLIC_FILES})


target_include_directories(gentlemanly_engine 
PRIVATE 
	${OPENGL_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
	${ASSIMP_INCLUDE_DIRS}
PUBLIC
	include
	${GLM_INCLUDE_DIR}
	entityx/
)

target_link_libraries(gentlemanly_engine
PRIVATE 
	${SDL2_LIBRARY}
	${OPENGL_LIBRARIES}
	${ASSIMP_LIBRARIES}
PUBLIC
	entityx_shared
	Qt5::Widgets
	Boost::filesystem
)


target_compile_features(gentlemanly_engine
PUBLIC
	cxx_aggregate_default_initializers
	cxx_generic_lambdas
	cxx_variadic_templates
)

# so other people can use it
install(DIRECTORY include/ge DESTINATION include)
install(FILES cmake/gentlemanly_engine-config.cmake cmake/modules/FindEntityX.cmake DESTINATION lib/gentlemanly_engine)

# Samples

if(BUILD_SAMPLES)
	add_subdirectory(samples)
endif()

# Documentation

find_package(Doxygen)

if(DOXYGEN_FOUND)

	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)

	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_EXTRA_FLAGS}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Generating Doxygen documentation..."
		DEPENDS ${GE_PRIVATE_FILES} ${GE_PUBLIC_FILES}
	)
		
else()
	message("If you want the target \"doc\" to be avaliable to build doxygen documentation, 
	then install Doxygen or if it is already installed, set DOXYGEN_EXECUTABLE with a path to doxygen.")
endif()
