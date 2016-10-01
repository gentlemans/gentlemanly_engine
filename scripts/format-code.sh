#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

clang-format -style=file -i $(find ge samples modules -name "*.cpp") $(find ge samples modules -name "*.hpp")

