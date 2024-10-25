################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_post SHARED
    post/post.cpp
    post/box/box.cpp
    post/testing/testing.cpp
)

target_link_libraries(yq_post PUBLIC
    yq_core 
)

LinkTest(yq_post)

