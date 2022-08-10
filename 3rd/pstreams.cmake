#   Simple cmake to configure rapid XML as an "interface" library
if(NOT TARGET pstreams)
    file( GLOB pstreams_dir ${CMAKE_CURRENT_LIST_DIR}/pstreams-*)
    add_library(pstreams INTERFACE)
    target_sources(pstreams INTERFACE
        ${pstreams_dir}/pstream.h
    )
    target_include_directories(pstreams INTERFACE ${pstreams_dir})
endif()

