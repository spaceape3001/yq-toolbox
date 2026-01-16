################################################################################
##
##  YOUR QUILL
##
################################################################################

cmake_minimum_required(VERSION 3.26.0)
project(YQ_Toolbox VERSION 0.0.0.3 LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
    set(YOUR_QUILL_TOOLBOX_STANDALONE ON)
endif()

include(local.cmake OPTIONAL)

set(YQ_TOOLBOX_ROOT ${CMAKE_CURRENT_LIST_DIR})
set_property(GLOBAL PROPERTY YQ_VULQAN_DATA ${YQ_TOOLBOX_ROOT}/data) 

set(TOOLBOX_API_DIR ${YQ_TOOLBOX_ROOT}/api)
set(TOOLBOX_DEV_DIR ${YQ_TOOLBOX_ROOT}/dev)

include(configure.cmake)
include(standard.cmake)

YQRepo()
