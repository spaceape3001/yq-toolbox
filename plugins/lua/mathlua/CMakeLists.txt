################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(mathlua SHARED 
    common.cpp
    trigonometry.cpp
)


target_link_libraries(mathlua PUBLIC yq_lua yq_math)
LinkTest(mathlua)
