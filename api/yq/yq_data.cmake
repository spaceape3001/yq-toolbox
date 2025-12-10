################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_data SHARED
    data/Gridded.cpp
)

target_link_libraries(yq_data PUBLIC
    yq_core yq_resource
)

LinkTest(yq_data)

