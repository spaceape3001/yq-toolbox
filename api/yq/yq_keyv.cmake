################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_keyv SHARED
    keyv/KeyValue.cpp
    keyv/StdFile.cpp
)

target_link_libraries(yq_keyv 
    PUBLIC
        yq_core 
        yq_file

    PRIVATE
        yq_xml
)

LinkTest(yq_keyv)

