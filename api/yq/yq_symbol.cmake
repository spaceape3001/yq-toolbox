################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_symbol SHARED
    symbol/symbol.cpp
    symbol/USymLoader.cpp
)

target_link_libraries(yq_symbol
PUBLIC 
    yq_core 
    yq_color 
    yq_math 
    yq_resource
    yq_b3fmt
)

LinkTest(yq_symbol)

