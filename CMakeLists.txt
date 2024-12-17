cmake_minimum_required(VERSION 3.22)

project(
  AdventOfCode
  VERSION 0.0.1
  LANGUAGES CXX)

# set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

add_compile_options(-Wall -Werror -Wpedantic)

add_subdirectory(./src)
