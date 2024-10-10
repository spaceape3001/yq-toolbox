################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_chemistry SHARED
    chemistry/Phase.cpp
)

target_link_libraries(yq_chemistry PUBLIC
    yq_core
)

LinkTest(yq_chemistry)

