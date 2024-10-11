#   Simple cmake to configure rapid XML as an "interface" library
if(NOT TARGET yq_pstreams)
    file( GLOB pstreams_dir ${CMAKE_CURRENT_LIST_DIR}/pstreams-*)
    add_library(yq_pstreams INTERFACE)
    target_sources(yq_pstreams INTERFACE
        ${pstreams_dir}/pstream.h
    )
    target_include_directories(yq_pstreams INTERFACE ${pstreams_dir})
endif()

