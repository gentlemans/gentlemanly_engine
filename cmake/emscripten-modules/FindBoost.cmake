

message("Using emscripten Boost")

add_library(Boost::filesystem STATIC IMPORTED)

set_property(TARGET Boost::filesystem PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/precompiled_emscripten_binaries/libboost_filesystem.a)

add_library(Boost::system STATIC IMPORTED)

set_property(TARGET Boost::system PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/precompiled_emscripten_binaries/libboost_system.a)

add_dependencies(Boost::filesystem Boost::system)

