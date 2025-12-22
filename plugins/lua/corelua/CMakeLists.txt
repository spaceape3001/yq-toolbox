################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(corelua SHARED
    debug.cpp
    help.cpp
    meta.cpp
    print.cpp
    stdtypes.cpp
    sys.cpp
    table.cpp
)
target_link_libraries(corelua PUBLIC yq_lua)
LinkTest(corelua)
