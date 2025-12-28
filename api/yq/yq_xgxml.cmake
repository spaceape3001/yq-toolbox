################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_xgxml SHARED
    xg/XGXmlIO.cpp
)

target_link_libraries(yq_xgxml 
PUBLIC 
    yq_xg
    yq_xml
)

LinkTest(yq_xgxml)
