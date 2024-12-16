################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_color SHARED
    color/HSL.cpp
    color/HSV.cpp
    color/RGBA.cpp
    color/RGB.cpp
)

target_link_libraries(yq_color PUBLIC
    yq_core yq_math
)

LinkTest(yq_color)

