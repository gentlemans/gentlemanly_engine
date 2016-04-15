#!/bin/bash


cd src

clang-format -style=file -i $(find . -name "*.cpp") $(find . -name "*.hpp")

cd ../include


clang-format -style=file -i  $(find . -name "*.hpp")
