################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(basicxg SHARED 
    ContinueXG.cpp
    DoneXG.cpp
)
target_link_libraries(basicxg PUBLIC yq_xg)
LinkTest(basicxg)
