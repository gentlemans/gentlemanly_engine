# Config script for gentlemanly_engine
# 
# Defines the variable: GENTLYMENLY_ENGINE_INCLUDE_DIRS
# Defines the imported target: gentlemanly_engine

get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/gentlemanly_engine-targets.cmake)

get_target_property(GENTLYMENLY_ENGINE_INCLUDE_DIRS gentlemanly_engine INTERFACE_INCLUDE_DIRECTORIES)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(gentlemanly_engine DEFAULT_MSG GENTLYMENLY_ENGINE_INCLUDE_DIRS)
