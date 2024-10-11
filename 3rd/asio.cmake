################################################################################
##
##  YOUR QUILL
##
################################################################################

if(Build_ASIO AND (NOT TARGET yq_asio))
    set(asio_dir ${CMAKE_CURRENT_LIST_DIR}/asio/asio)
    add_library(yq_asio INTERFACE)
    target_sources(yq_asio INTERFACE
        ${asio_dir}/include/asio.hpp
    )
    target_include_directories(yq_asio INTERFACE ${asio_dir}/include)
endif()

