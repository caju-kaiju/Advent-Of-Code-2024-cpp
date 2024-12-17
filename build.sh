#!/bin/bash

# Exit on the first error
set -e

echo "Beginning Cmake"
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release

echo "Beginning Make"
make -C ./build/
