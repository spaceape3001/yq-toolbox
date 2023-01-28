if(NOT YOUR_QUILL_TOOLBOX)

    if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
            # Mixing source and binary output is asking for trouble, best to avoid it
        message(SEND_ERROR "Building into the source directory is NOT recommended, choose another destination.")
    endif()

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "12.0.0")
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

    #option(Feature_ApiDocumentation "Enable Doxygen API Generation?" ON)
    option(Feature_BuildTime "Print out build times" ON)
    # option(Feature_PrecompiledHeaders "Enable Precompiled Headers" ON)
    option(Developer_Build "Set for a development build" ON) # Disable for release-release

    message( "Build Type is " ${CMAKE_BUILD_TYPE})

    #   WARNING DEFINITIONS
    add_definitions(
        -Wfatal-errors 
        -Wno-error=suggest-override
        -Wno-error=unused-function 
        -Wno-error=unused-variable 
        -Wall 
        -Wextra
        -fno-strict-aliasing 
        -D_GNU_SOURCE 
        -fdiagnostics-color 
        -fdiagnostics-show-template-tree 
        -fno-elide-type 
        -fdiagnostics-path-format=inline-events 
        -fdiagnostics-generate-patch
    )

    enable_testing()

    if(Feature_BuildTime)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
    endif()

    SET(YOUR_QUILL_TOOLBOX ${CMAKE_CURRENT_LIST_DIR})
endif()





