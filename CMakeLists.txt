cmake_minimum_required(VERSION 4.4)
project(example)

set (CMAKE_CXX_STANDARD 26)
set (CMAKE_EXPORT_COMPILE_COMMANDS on)

file (GLOB_RECURSE SOURCES CONFIGURE_DEPENDS abgabe1/*.cpp)

add_executable (example_exe ${SOURCES})

