cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(pugixml)

file(GLOB PG_PUGIXML *.hpp)
file(GLOB HD_PUGIXML *.cpp)

add_library(pugixml ${PG_PUGIXML} ${HD_PUGIXML})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)