################################################################################
##
##  YOUR QUILL
##
################################################################################

##
##  Given the presence of a numerous number of sub-projects, we're harmonizing
##
##  So, include this file :)
##

if(NOT DEFINED YOUR_QUILL_STANDARD_CMAKE)
    message("Using standard.cmake")
    set(YOUR_QUILL_STANDARD_CMAKE ON)   ## prevent recursion

    ####################
    #   User features

    option(Feature_BuildTime    "Print out build times" OFF)
        
    if(EXISTS ${CMAKE_SOURCE_DIR}/yq-doodle)
        option(Feature_Doodle   "Enable the doodle API and features" ON)
        set(Build_Doodle ${Feature_Doodle})
    else()
        set(Build_Doodle OFF)
    endif()

    option(Feature_Doxygen      "Build doxygen documentation" OFF)

    option(Feature_Experimental "Enable Experimental Features" ON)

    if(EXISTS ${CMAKE_SOURCE_DIR}/yq-novel)
        option(Feature_Novel   "Enable the novel API and features" ON)
        set(Build_Novel ${Feature_Novel})
    else()
        set(Build_Novel OFF)
    endif()

    if(EXISTS ${CMAKE_SOURCE_DIR}/qt-utilities)
        option(Feature_Qt6      "Enable Qt6 (API and Apps)" ON)
        set(Build_Qt6 ${Feature_Qt6})
    else()
        set(Build_Qt6 OFF)
    endif()

    if(EXISTS ${CMAKE_SOURCE_DIR}/yq-rocks)
        option(Feature_Rocks      "Enable Rocks" ON)
        set(Build_Rocks ${Feature_Qt6})
    else()
        set(Build_Rocks OFF)
    endif()

    option(Feature_SDK          "Enable SDK (Apps)" ON)
    option(Feature_UnitTests    "Enable Unit Tests" ON)

    if(EXISTS ${CMAKE_SOURCE_DIR}/yq-vulqan)
        option(Feature_Vulkan   "Enable Vulkan (API and Apps)" ON)
        set(Build_Vulkan ${Feature_Vulkan})
    else()
        set(Build_Vulkan OFF)
    endif()

    if(EXISTS ${CMAKE_SOURCE_DIR}/yq-quill)
        option(Feature_YQuill   "Build Your Quill" ON)
        set(Build_YQuill ${Feature_YQuill})
    else()
        set(Build_YQuill OFF)
    endif()

    # option(Feature_WebServer    "Enable Web Server" ON)
    
    ####################
    #   Translate any of the above into build flags
    
    set(Build_ASIO          ON)
    set(Build_CURL          ON)
    set(Build_Doxygen       ${Feature_Doxygen})
    set(Build_GLM           ${Feature_Vulkan})
    set(Build_SDK           ${Feature_SDK})
    set(Build_SQL           ON)
    set(Build_Timing        ${Feature_BuildTime})
    set(Build_UnitTests     ${Feature_UnitTests})

    include(${CMAKE_SOURCE_DIR}/yq-toolbox/configure.cmake)
    add_subdirectory(${CMAKE_SOURCE_DIR}/yq-toolbox)

    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

    if(Build_Vulkan)
        include(${CMAKE_SOURCE_DIR}/yq-vulqan/configure.cmake)
        add_subdirectory(${CMAKE_SOURCE_DIR}/yq-vulqan)
    endif()

    if(Build_Qt6)
        add_subdirectory(${CMAKE_SOURCE_DIR}/qt-utilities)
    endif()

    if(Build_Doodle)
        include(${CMAKE_SOURCE_DIR}/yq-doodle/configure.cmake)
        add_subdirectory(${CMAKE_SOURCE_DIR}/yq-doodle)
    endif()

    if(Build_Novel)
        include(${CMAKE_SOURCE_DIR}/yq-novel/configure.cmake)
        add_subdirectory(${CMAKE_SOURCE_DIR}/yq-novel)
    endif()

    if(Build_Rocks)
        include(${CMAKE_SOURCE_DIR}/yq-rocks/configure.cmake)
        add_subdirectory(${CMAKE_SOURCE_DIR}/yq-rocks)
    endif()

    if(${Build_UnitTests})
        enable_testing()
    endif()

    if(Build_YQuill)
        include(yq-quill/${CMAKE_SOURCE_DIR}/configure.cmake)
        add_subdirectory(${CMAKE_SOURCE_DIR}/yq-quill)
    endif()
endif()

#### This is the standard root macro to call after include()
macro(YQRepo)
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/3rd)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/dev)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dev)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/api)
        include_directories(api)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/api)
    endif()
    if(Feature_Experimental AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/apix)
        include_directories(apix)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/apix)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/plugins)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/plugins)
    endif()
    if(Feature_Experimental AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/pluginx)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/pluginx)
    endif()
    if(Build_UnitTests AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/test)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
    endif()
    if(Feature_Experimental AND Build_UnitTests AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/testx)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/testx)
    endif()
    if(Build_SDK AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/sdk)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/sdk)
    endif()
    if(Feature_Experimental AND Build_SDK AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/sdkx)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/sdkx)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/tool)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tool)
    endif()
    if(Feature_Experimental AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/toolx)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/toolx)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/exe)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/exe)
    endif()
    if(Feature_Experimental AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/exex)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/exex)
    endif()
    if(Feature_Experimental AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/playx)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/playx)
    endif()
endmacro()
