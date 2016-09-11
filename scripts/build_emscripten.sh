#!/bin/bash


set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ ! -f $EMSCRIPTEN_DIR/emcc ]; then
	echo "Please set the environment variable EMSCRIPTEN_DIR to the install directory of emscripten"
	exit 
fi

SOURCES="src/ge/material.cpp
src/ge/sdl_viewport.cpp
src/ge/shader.cpp
src/ge/collision_controller.cpp
src/ge/json/json_reader.cpp
src/ge/json/json_value.cpp
src/ge/json/json_writer.cpp
src/ge/material_asset.cpp
src/ge/sdl_application.cpp
src/ge/mesh.cpp
src/ge/sdl_window.cpp
src/ge/actor.cpp
src/ge/model_actor.cpp
src/ge/mesh_asset.cpp
src/ge/asset_manager.cpp"

EXTRA_FLAGS="$@"

mkdir -p build

$EMSCRIPTEN_DIR/emcc -DEMSCRIPTEN=1 -s USE_SDL=2 $SOURCES $DIR/precompiled_emscripten_binaries/libboost_filesystem.bc $DIR/precompiled_emscripten_binaries/libboost_system.bc $DIR/precompiled_emscripten_binaries/libtinyobjloader.bc $DIR/precompiled_emscripten_binaries/libBox2D.bc -I $DIR/include $EXTRA_FLAGS -std=c++14 -o build/libgentlemanly_engine.bc
