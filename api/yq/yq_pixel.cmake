################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_pixel SHARED
    pixel/Painter.cpp
    pixel/Pixmap.cpp
)

target_link_libraries(yq_pixel 
    PUBLIC
        yq_core 
        yq_color
)

LinkTest(yq_pixel)

