################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_raster SHARED
    raster/raster.cpp
)

target_link_libraries(yq_raster 
    PUBLIC
        yq_core 
        yq_color
)

LinkTest(yq_raster)

