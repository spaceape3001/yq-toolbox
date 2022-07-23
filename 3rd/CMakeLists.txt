file( GLOB json_dir json-nlohmann-*)
add_library(json INTERFACE)
target_sources(json INTERFACE
    ${json_dir}/include/nlohmann/json.hpp
)
target_include_directories(json INTERFACE ${json_dir}/include)

