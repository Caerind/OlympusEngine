cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(OlympusEngine C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

add_subdirectory(Sources/ExtLibs/pugixml)
add_subdirectory(Sources/ExtLibs/miniz)

file(GLOB_RECURSE PG_OLYMPUS Sources/*.hpp)
file(GLOB_RECURSE HD_OLYMPUS Sources/*.cpp)

set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)

find_package(SFML 2 REQUIRED graphics window system network audio)
add_subdirectory(Sources/ExtLibs/imgui)
find_package(OpenGL REQUIRED)

include_directories(Sources/ExtLibs)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

MESSAGE(${SFML_INCLUDE_DIR})

add_executable(OlympusEngine ${PG_OLYMPUS} ${HD_OLYMPUS})

target_link_libraries(OlympusEngine pugixml)
target_link_libraries(OlympusEngine miniz)
target_link_libraries(OlympusEngine imgui)

if(SFML_FOUND)
  target_link_libraries(OlympusEngine ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(OlympusEngine ${OPENGL_LIBRARIES})