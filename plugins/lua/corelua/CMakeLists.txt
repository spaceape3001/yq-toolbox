################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(corelua SHARED 
    help.cpp
    meta.cpp
    print.cpp
    stdtypes.cpp
)
target_link_libraries(corelua PUBLIC yq_lua)
LinkTest(corelua)
