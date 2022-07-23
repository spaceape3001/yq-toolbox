file( GLOB json_dir json-nlohmann-*)
add_library(json INTERFACE)
target_sources(json INTERFACE
    ${json_dir}/include/nlohmann/json.hpp
)
target_include_directories(json INTERFACE ${json_dir}/include)

file( GLOB pstreams_dir pstreams-*)
add_library(pstreams INTERFACE)
target_sources(pstreams INTERFACE
    ${pstreams_dir}/pstream.h
)
target_include_directories(pstreams INTERFACE ${pstreams_dir})

