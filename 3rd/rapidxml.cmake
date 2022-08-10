#   Simple cmake to configure rapid XML as an "interface" library
if(NOT TARGET RapidXml)
    file( GLOB rapidxml_dir ${CMAKE_CURRENT_LIST_DIR}/rapidxml-*)
    add_library(RapidXml INTERFACE)
    target_sources(RapidXml INTERFACE
        ${rapidxml_dir}/rapidxml.hpp 
        ${rapidxml_dir}/rapidxml_iterators.hpp 
        ${rapidxml_dir}/rapidxml_print.hpp 
        ${rapidxml_dir}/rapidxml_utils.hpp
    )
    target_include_directories(RapidXml INTERFACE ${rapidxml_dir})
endif()

