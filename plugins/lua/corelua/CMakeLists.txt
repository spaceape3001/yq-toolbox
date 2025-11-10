################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(corelua SHARED help.cpp)
target_link_libraries(corelua PUBLIC yq_lua)
LinkTest(corelua)
