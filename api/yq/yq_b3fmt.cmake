################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_b3fmt SHARED
    b3fmt/b3fmt.cpp
)

target_link_libraries(yq_b3fmt
PUBLIC 
    yq_core 
    yq_color 
    yq_math 
)

LinkTest(yq_b3fmt)

