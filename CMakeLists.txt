################################################################################
##
##  YOUR QUILL
##
################################################################################

cmake_minimum_required(VERSION 3.26.0)

if("${PROJECT_NAME}" STREQUAL "")
    project(YourQuill VERSION 0.0.0.3)
endif()
include(configure.cmake)

add_subdirectory(3rd)
add_subdirectory(api)
if(Build_UnitTests)
    add_subdirectory(test)
endif()
if(Build_SDK)
    add_subdirectory(sdk)
endif()
add_subdirectory(tool)

