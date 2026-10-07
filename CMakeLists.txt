
cmake_minimum_required(VERSION 3.20)
project(prog3)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB children CONFIGURE_DEPENDS LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/*/*/CMakeLists.txt)

foreach(cmake_file ${children})
    file(TO_CMAKE_PATH ${cmake_file} ccmake_file)
    cmake_path(GET ccmake_file PARENT_PATH dir)
    message(STATUS "Building ${dir}")
    add_subdirectory(${dir})
endforeach()


