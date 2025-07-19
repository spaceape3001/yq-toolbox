################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_resource SHARED
    resource/resource.cpp
)

target_link_libraries(yq_resource 
    PUBLIC
        yq_core 
    PRIVATE
        yq_file
        yq_keyv
        yq_json
        yq_xml
)

LinkTest(yq_resource)

