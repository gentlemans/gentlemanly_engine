cmake_minimum_required(VERSION 2.6)
project(gentlemanly_engine)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

set(DOXYGEN_EXTRA_FLAGS "" CACHE STRING "Extra flags to be sent to doxygen.")


# update the module path so cmake can find libraries that don't have built in CMake support
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)


# find packages
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(TinyObjLoader REQUIRED)
find_package(Box2D REQUIRED)


find_package(Qt5Widgets REQUIRED)

# emscripten includes this automatially
find_package(SDL2 REQUIRED)

# GLM_INCLUDE_DIR has to be manually set
find_package(glm REQUIRED)


set(GE_PRIVATE_FILES
	
	src/ge/sdl_application.cpp
	src/ge/sdl_window.cpp
	src/ge/sdl_viewport.cpp
	
	src/ge/qt_application.cpp
	src/ge/qt_window.cpp
	src/ge/qt_viewport.cpp
	
	src/ge/actor.cpp
	src/ge/asset_manager.cpp
	src/ge/material.cpp
	src/ge/material_asset.cpp
	src/ge/mesh.cpp
	src/ge/mesh_asset.cpp
	src/ge/model.cpp
	src/ge/physics_world.cpp
	src/ge/shader.cpp
	
	# JSONCPP
	src/ge/json/json_reader.cpp
	src/ge/json/json_tool.h
	src/ge/json/json_value.cpp
	src/ge/json/json_valueiterator.inl
	src/ge/json/json_writer.cpp
	
	
)

set(GE_PUBLIC_FILES 
	include/ge/concept/variadic_concept.hpp
	include/ge/concept/viewport.hpp
	include/ge/concept/window.hpp
	include/ge/concept/application.hpp
	
	include/ge/qt_application.hpp
	include/ge/qt_window.hpp
	include/ge/qt_viewport.hpp
	
	include/ge/sdl_application.hpp
	include/ge/sdl_window.hpp
	include/ge/sdl_viewport.hpp
	
	include/ge/actor.hpp
	include/ge/asset.hpp
	include/ge/asset_manager.hpp
	include/ge/camera.hpp
	include/ge/material.hpp
	include/ge/mesh.hpp
	include/ge/model.hpp
	include/ge/ortho2d.hpp
	include/ge/physics_world.hpp
	include/ge/shader.hpp
	
	#JSONCPP
	include/ge/json/allocator.h
	include/ge/json/assertions.h
	include/ge/json/autolink.h
	include/ge/json/config.h
	include/ge/json/features.h
	include/ge/json/forwards.h
	include/ge/json/json.h
	include/ge/json/reader.h
	include/ge/json/value.h
	include/ge/json/version.h
	include/ge/json/writer.h
)



add_library(gentlemanly_engine SHARED ${GE_PRIVATE_FILES} ${GE_PUBLIC_FILES})


target_include_directories(gentlemanly_engine 
PRIVATE 
	include
	${OPENGL_INCLUDE_DIR}
	${TINYOBJLOADER_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
INTERFACE 
	${CMAKE_INSTALL_PREFIX}/include
PUBLIC 
	${BOX2D_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${GLM_INCLUDE_DIR}
)

target_link_libraries(gentlemanly_engine
PUBLIC
	Qt5::Widgets
PRIVATE 
	${BOX2D_LIBRARIES}
	${SDL2_LIBRARY}
	${OPENGL_LIBRARIES}
	${TINYOBJLOADER_LIBRARY}
	Boost::filesystem
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
