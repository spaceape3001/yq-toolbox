################################################################################
##
##  YOUR QUILL
##
################################################################################

#   Simple cmake to configure rapid XML as an "interface" library
if(NOT TARGET yq_rapidxml)
    set(rapidxml_dir ${CMAKE_CURRENT_LIST_DIR}/rapidxml)
    add_library(yq_rapidxml INTERFACE)
    target_sources(yq_rapidxml INTERFACE
        ${rapidxml_dir}/rapidxml.hpp 
        ${rapidxml_dir}/rapidxml_iterators.hpp 
        ${rapidxml_dir}/rapidxml_print.hpp 
        ${rapidxml_dir}/rapidxml_utils.hpp
    )
    target_include_directories(yq_rapidxml INTERFACE ${rapidxml_dir})
endif()

