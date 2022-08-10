if(NOT TARGET json)
    set(json_dir ${CMAKE_CURRENT_LIST_DIR}/json)
    add_library(json INTERFACE)
    target_sources(json INTERFACE
        ${json_dir}/include/nlohmann/json.hpp
    )
    target_include_directories(json INTERFACE ${json_dir}/include)
endif()

