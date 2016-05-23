#!/bin/bash


clang-format -style=file -i $(find include src samples -name "*.cpp") $(find include src samples -name "*.hpp")

