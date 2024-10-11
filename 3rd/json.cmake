################################################################################
##
##  YOUR QUILL
##
################################################################################

if(NOT TARGET yq_json)
    set(json_dir ${CMAKE_CURRENT_LIST_DIR}/json)
    add_library(yq_json INTERFACE)
    target_sources(yq_json INTERFACE
        ${json_dir}/include/nlohmann/json.hpp
    )
    target_include_directories(yq_json INTERFACE ${json_dir}/include)
endif()

