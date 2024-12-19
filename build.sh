#!/bin/bash

# Exit on the first error
set -e

echo "Beginning Cmake"
cmake -S . -B ./build

echo "Beginning Make"
make -C ./build/
