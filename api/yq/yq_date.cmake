################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_date SHARED
    date/date.cpp
)

target_link_libraries(yq_date PUBLIC
    yq_core
)

LinkTest(yq_date)

