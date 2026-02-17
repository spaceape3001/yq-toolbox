################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_graph SHARED
    graph/GraphData.cpp
    graph/GDocument.cpp
    graph/GMetaGraph.cpp
    graph/GNodeObject.cpp
    graph/GNodeTemplate.cpp
    graph/GraphXML.cpp
)

target_link_libraries(yq_graph PUBLIC
    yq_core 
    yq_xml 
    yq_resource
    yq_symbol
)

LinkTest(yq_graph)

