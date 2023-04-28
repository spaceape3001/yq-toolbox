cmake_minimum_required(VERSION 3.26.0)

if("${PROJECT_NAME}" STREQUAL "")
    project(YourQuill VERSION 0.0.0.3)
endif()
include(configure.cmake)

add_subdirectory(3rd)
add_subdirectory(api)
add_subdirectory(test)
add_subdirectory(tool)

