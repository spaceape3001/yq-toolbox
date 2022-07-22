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

file( GLOB rapidxml_dir rapidxml-*)
add_library(RapidXml INTERFACE)
target_sources(RapidXml INTERFACE
    ${rapidxml_dir}/rapidxml.hpp 
    ${rapidxml_dir}/rapidxml_iterators.hpp 
    ${rapidxml_dir}/rapidxml_print.hpp 
    ${rapidxml_dir}/rapidxml_utils.hpp
)
target_include_directories(RapidXml INTERFACE ${rapidxml_dir})

file( GLOB ut_dir ut-*)
add_library(BoostUT INTERFACE)
target_sources(BoostUT INTERFACE
    ${ut_dir}/include/boost/ut.hpp
)
target_include_directories(BoostUT INTERFACE ${ut_dir}/include)


