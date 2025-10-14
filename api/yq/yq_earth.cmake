################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_earth SHARED
    earth/GeoBody.cpp
)

target_link_libraries(yq_earth PUBLIC
    yq_math
    yq_core
)

LinkTest(yq_earth)
