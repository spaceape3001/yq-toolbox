################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_graph SHARED
    #graph/GraphSymbol.cpp
    graph/GraphIO.cpp
    graph/GNodeObject.cpp
    graph/GNodeTemplate.cpp
    graph/graph.cpp
    graph/GPinFlow.cpp
)

target_link_libraries(yq_graph PUBLIC
    yq_core 
    yq_xml 
    yq_resource
)

LinkTest(yq_graph)

