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

set(YQ_TOOLBOX_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(TOOLBOX_API_DIR ${YQ_TOOLBOX_ROOT}/api)
set(TOOLBOX_DEV_DIR ${YQ_TOOLBOX_ROOT}/dev)

add_subdirectory(3rd)
add_subdirectory(dev)
add_subdirectory(api)
if(Build_UnitTests)
    add_subdirectory(test)
endif()
if(Build_SDK)
    add_subdirectory(sdk)
endif()
add_subdirectory(tool)

