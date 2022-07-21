cmake_minimum_required(VERSION 3.23.0)

project(YourQuill VERSION 0.0.0.3)
include(YourQuill.cmake)

add_subdirectory(3rd)
add_subdirectory(api)
add_subdirectory(test)
add_subdirectory(tool)

