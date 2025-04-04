################################################################################
##
##  YOUR QUILL
##
################################################################################

cmake_minimum_required(VERSION 3.26.0)
project(YQ_Toolbox VERSION 0.0.0.3 LANGUAGES CXX)
include(local.cmake OPTIONAL)
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

#   Not in GIT, but a spot to experiement
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/apix)
    add_subdirectory(apix)
endif()
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/testx)
    add_subdirectory(testx)
endif()
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/toolx)
    add_subdirectory(toolx)
endif()
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/exex)
    add_subdirectory(exex)
endif()
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/sdkx)
    add_subdirectory(sdkx)
endif()
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/playx) 
    add_subdirectory(playx)
endif()
