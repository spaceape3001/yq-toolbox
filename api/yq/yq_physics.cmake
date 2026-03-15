################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_physics SHARED
)

target_link_libraries(yq_physics PUBLIC
    yq_core
)

LinkTest(yq_physics)

