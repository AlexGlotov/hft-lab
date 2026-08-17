cmake_minimum_required(VERSION 3.28)

project(hft-lab
    LANGUAGES CXX
    DESCRIPTION "Low-latency C++ experiments, reusable building blocks and benchmarks"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerOptions)

enable_testing()
add_subdirectory(experiments)