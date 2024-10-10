################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_color SHARED
    color/color.cpp
)

target_link_libraries(yq_color PUBLIC
    yq_core yq_math
)

LinkTest(yq_color)

