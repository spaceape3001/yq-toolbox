################################################################################
##
##  YOUR QUILL
##
################################################################################

project(basicxg)
add_library(${PROJECT_NAME} SHARED 
    AlwaysXG.cpp
    ContinueXG.cpp
    DelayXG.cpp
    DoneXG.cpp
    ResumeXG.cpp
    StartXG.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC yq_xg)
LinkTest(${PROJECT_NAME})
