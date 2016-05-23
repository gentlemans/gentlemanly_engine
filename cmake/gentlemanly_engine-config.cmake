# Config script for gentlemanly_engine
# 
# Defines the imported target: gentlemanly_engine

get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${SELF_DIR})


find_package(Qt5Widgets REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(EntityX)
find_package(glm REQUIRED)

find_path(GENTLYMENLY_ENGINE_INCLUDE_DIRS 
	ge/world.hpp
HINTS
	/usr/include
)

find_library(GENTLYMENLY_ENGINE_LIBRARY
	gentlemanly_engine
HINTS
	/usr/lib
)

add_library(gentlemanly_engine IMPORTED)
set_property(TARGET gentlemanly_engine
PROPERTY INCLUDE_DIRECTORIES 
	${GENTLYMENLY_ENGINE_INCLUDE_DIRS}
	${GLM_INCLUDE_DIR}
)

set_property(TARGET gentlemanly_engine
PROPERTY LINK_LIBRARIES
	${GENTLYMENLY_ENGINE_LIBRARY}
	EntityX
	Qt5::Widgets
	Boost::filesystem
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(gentlemanly_engine DEFAULT_MSG GENTLYMENLY_ENGINE_INCLUDE_DIRS GENTLYMENLY_ENGINE_LIBRARY)
