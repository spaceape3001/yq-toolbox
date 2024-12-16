################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_graph SHARED
    graph/GraphIO.cpp
    graph/graph.cpp
    graph/PinFlow.cpp
)

target_link_libraries(yq_graph PUBLIC
    yq_core yq_xml
)

LinkTest(yq_graph)

