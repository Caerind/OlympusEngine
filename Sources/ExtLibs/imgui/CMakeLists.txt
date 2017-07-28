cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(imgui)

file(GLOB PG_IMGUI *.h)
file(GLOB HD_IMGUI *.cpp)

include_directories(${SFML_INCLUDE_DIR})

add_library(imgui ${PG_IMGUI} ${HD_IMGUI})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)