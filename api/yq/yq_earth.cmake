################################################################################
##
##  YOUR QUILL
##
################################################################################


add_library(yq_earth SHARED
    earth/earthcoords.cpp
)

target_link_libraries(yq_earth PUBLIC
    yq_core yq_math
)

LinkTest(yq_earth)

