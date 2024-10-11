################################################################################
##
##  YOUR QUILL
##
################################################################################

if(NOT YOUR_QUILL_TOOLBOX)

    message("Configuring this project that's leveraging the Your Quill Toolbox")

    if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
            # Mixing source and binary output is asking for trouble, best to avoid it
        message(SEND_ERROR "Building into the source directory is NOT recommended, choose another destination.")
    endif()

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "13.0.0")
            message(FATAL_ERROR "GCC version is obsolete, upgrade.")
        endif()
        SET(GCC ON)
    else()
        SET(GCC OFF)
    endif()

    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
        set(CMAKE_GENERATOR "Unix Makefiles")
        get_filename_component(CMAKE_BUILD_TYPE ${CMAKE_BINARY_DIR} NAME)
    endif()

    set(CMAKE_CONFIGURATION_TYPES Debug;Release)
    set(CMAKE_CXX_STANDARD 23)                  # C++23 is the standard (may be bumped in the future)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_DEBUG_POSTFIX D)


    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

    include(GroupFiles)
    include(LinkTest)

    #   Build Flags
    #   
    #   These are so users can customize how the toolbox/suite is built.
    #   At *this* point, options should have been already set, so default
    #   them to OFF if unspecified.
    #
    if(NOT DEFINED Build_ASIO)
        set(Build_ASIO          OFF)
    endif()
    if(NOT DEFINED Build_CURL)
        set(Build_CURL          OFF)
    endif()
    if(NOT DEFINED Build_Doxygen)
        set(Build_Doxygen       OFF)
    endif()
    if(NOT DEFINED Build_GLM)
        set(Build_GLM           OFF)
    endif()
    if(NOT DEFINED Build_Qt6)
        set(Build_Qt6           OFF)
    endif()
    if(NOT DEFINED Build_SDK)
        set(Build_SDK           OFF)
    endif()
    if(NOT DEFINED Build_SQL)
        set(Build_SQL           OFF)
    endif()
    if(NOT DEFINED Build_Timing)
        set(Build_Timing        OFF)
    endif()
    if(NOT DEFINED Build_UnitTests)
        set(Build_UnitTests     OFF)
    endif()
    if(NOT DEFINED Build_Vulkan)
        set(Build_Vulkan        OFF)
    endif()
    

    #option(Feature_ApiDocumentation "Enable Doxygen API Generation?" ON)
    # option(Feature_PrecompiledHeaders "Enable Precompiled Headers" ON)
    # option(Developer_Build "Set for a development build" ON) # Disable for release-release

    message( "Build Type is " ${CMAKE_BUILD_TYPE})

    #   WARNING DEFINITIONS
    add_definitions(
        -Wfatal-errors 
        -Wno-error=suggest-override
        -Wno-error=unused-function 
        -Wno-error=unused-variable 
        -Wall 
        -fno-strict-aliasing 
        -D_GNU_SOURCE 
        -fdiagnostics-color 
        -fdiagnostics-show-template-tree 
        -fno-elide-type 
        -fdiagnostics-path-format=inline-events 
        -fdiagnostics-generate-patch
    )
    
    if(Build_ASIO)
        message("Configuring to use ASIO")
        add_definitions(-DASIO_STANDALONE -DYQ_USE_ASIO=1)
    endif()

    if(Build_CURL)
        message("Configuring to use CURL")
        add_definitions(-DYQ_USE_CURL=1)
        find_package(CURL REQUIRED)
    endif()

    if(Build_Doxygen)
        message("Configuring to use Doxygen")
        find_package(Doxygen REQUIRED)
    endif()

    if(Build_GLM)
        message("Configuring to use GLM")
        add_definitions(-DYQ_USE_GLM=1)
        find_package(glm 1.0.0 REQUIRED)
    endif()

    if(Build_Qt6)
        message("Configuring to use Qt6")
        add_definitions(-DYQ_USE_QT=1 -DYQ_USE_QT6=1)
    endif()

    if(Build_SQL)
        message("Configuring to use SQL")
        add_definitions(-DYQ_USE_SQL=1)
        find_package(SQLite3 REQUIRED)
    endif()

    if(Build_SDK)   
        message("Configuring to generate SDK")
    endif()

    if(Build_Timing)
        message("Configuring to log build timing")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
    endif()

    if(Build_UnitTests)
        message("Configuring to generate unit tests")
        enable_testing()
    endif()
    
    if(Build_Vulkan)
        message("Configuring to use Vulkan")
        add_definitions(-DYQ_USE_VULKAN=1)
    endif()

    SET(YOUR_QUILL_TOOLBOX ${CMAKE_CURRENT_LIST_DIR})

    # Things we generally need....
    find_package(PkgConfig REQUIRED)

endif()





