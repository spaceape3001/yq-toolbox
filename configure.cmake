if(NOT YOUR_QUILL_TOOLBOX)
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





