################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_asset SHARED
    asset/asset.cpp
)

target_link_libraries(yq_asset 
    PUBLIC
        yq_core 
    PRIVATE
        yq_file
        yq_keyv
        yq_json
        yq_xml
)

LinkTest(yq_asset)

