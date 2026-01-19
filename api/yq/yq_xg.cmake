################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_xg SHARED
    xg/XGDocument.cpp
    xg/XGElement.cpp
    xg/XGManifest.cpp
    #xg/XGNodeMeta.cpp
    xg/XGNodeType.cpp
    xg/XGRuntime.cpp
)

target_link_libraries(yq_xg 
PUBLIC 
    yq_core 
    yq_color 
    yq_math 
    yq_resource
    yq_graph
)

LinkTest(yq_xg)

