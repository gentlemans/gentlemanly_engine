# Config script for gentlemanly_engine
# 
# Defines the variable: GENTLYMENLY_ENGINE_INCLUDE_DIRS
# Defines the imported target: gentlemanly_engine

get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/gentlemanly_engine-targets.cmake)
get_filename_component(GENTLYMENLY_ENGINE_INCLUDE_DIRS "${SELF_DIR}/../../include/" ABSOLUTE)
