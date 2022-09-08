cmake_minimum_required(VERSION 3.0)
project(DMathLib)

set(CMAKE_BINARY_DIR ./build)

aux_source_directory(./source SOURCE)
add_library(DMath STATIC ${SOURCE})
target_include_directories(DMath PUBLIC ./include)
