################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_userexpr SHARED
    userexpr/userexpr.cpp
    userexpr/impl/impl.cpp
    userexpr/opcode/opcode.cpp
)

target_link_libraries(yq_userexpr PUBLIC
    yq_core
    yq_math
)

LinkTest(yq_userexpr)

