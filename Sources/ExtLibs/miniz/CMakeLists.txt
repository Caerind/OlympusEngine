cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(miniz)

file(GLOB HD_MINIZ *.c)

add_library(miniz ${HD_MINIZ})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)