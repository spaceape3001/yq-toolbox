if(NOT YOUR_QUILL_TOOLBOX)
    if(NOT YOUR_QUILL_EXTERNAL)
        if(exists ${CMAKE_CURRENT_LIST_DIR}/../yq-external})
            include(../yq-external/configure.cmake)
        elseif(exists "$ENV{YOUR_QUILL_EXTERNAL}")
            include("$ENV{YOUR_QUILL_EXTERNAL}/configure.cmake")
        else()
            message(FATAL_ERROR "Unable to locate yq-external, install and set YOUR_QUILL_EXTERNAL environment variable")
        endif()
    endif()

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

    enable_testing()

    if(Feature_BuildTime)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
    endif()

    SET(YOUR_QUILL_TOOLBOX ${CMAKE_CURRENT_LIST_DIR})
endif()





