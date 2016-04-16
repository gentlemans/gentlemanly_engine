#!/bin/bash


set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ ! -f $EMSCRIPTEN_DIR/emcc ]; then
	echo "Please set the environment variable EMSCRIPTEN_DIR to the install directory of emscripten"
	exit 
fi

SOURCES="src/ge/window_backend/sdl.cpp
	src/ge/window_backend/sdl_window.cpp
	src/ge/window_backend/sdl_viewport.cpp
	
	src/ge/actor.cpp
	src/ge/application.cpp
	src/ge/asset_manager.cpp
	src/ge/material.cpp
	src/ge/material_asset.cpp
	src/ge/mesh.cpp
	src/ge/mesh_asset.cpp
	src/ge/model.cpp
	src/ge/physics_world.cpp
	src/ge/shader.cpp
	
	src/ge/json/json_reader.cpp
	src/ge/json/json_value.cpp
	src/ge/json/json_writer.cpp"

EXTRA_FLAGS="$@"

mkdir -p build

$EMSCRIPTEN_DIR/emcc -s -DEMSCRIPTEN=1 USE_SDL=2 $SOURCES $DIR/precompiled_emscripten_binaries/libboost_filesystem.bc $DIR/precompiled_emscripten_binaries/libboost_system.bc $DIR/precompiled_emscripten_binaries/libtinyobjloader.bc $DIR/precompiled_emscripten_binaries/libBox2D.bc -I $DIR/include $EXTRA_FLAGS -std=c++14 -o build/libgentlemanly_engine.bc
