#!/bin/bash


set -e

GAME_DIR=`pwd`

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ ! -f $EMSCRIPTEN_DIR/emcc ]; then
	echo "Please set the environment variable EMSCRIPTEN_DIR to the install directory of emscripten"
	exit 
fi

if [ ! -f $DIR/build/libgentlemanly_engine.bc ]; then
	echo "Please run ./build_emscripten.sh first"
	exit
fi

EXTRA_FLAGS="$@"

$EMSCRIPTEN_DIR/emcc -s -DEMSCRIPTEN=1 USE_SDL=2 $EXTRA_FLAGS $DIR/build/libgentlemanly_engine.bc -I $DIR/include -o index.html -std=c++14


