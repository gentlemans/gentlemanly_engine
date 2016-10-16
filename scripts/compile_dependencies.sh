#!/bin/bash

set -xe

SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

GE_DIR=$SCRIPTS_DIR/..
DEPS_DIR=$GE_DIR/deps
BUILD_DIR=$DEPS_DIR/build
INSTALL_DIR=$DEPS_DIR/install

#rm -rf $BUILD_DIR
#rm -rf $INSTALL_DIR

mkdir -p $BUILD_DIR
mkdir -p $INSTALL_DIR

cd $BUILD_DIR
cmake .. -G"Unix Makefiles" 
cmake --build . --target install
