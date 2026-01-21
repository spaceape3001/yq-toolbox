################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_graph SHARED
    graph/GraphData.cpp
    graph/GraphDocument.cpp
    graph/GNodeLibrary.cpp
    graph/GNodeObject.cpp
    graph/GNodeTemplate.cpp
)

target_link_libraries(yq_graph PUBLIC
    yq_core 
    yq_xml 
    yq_resource
)

LinkTest(yq_graph)

