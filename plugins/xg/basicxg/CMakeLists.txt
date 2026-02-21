################################################################################
##
##  YOUR QUILL
##
################################################################################

project(basicxg)
add_library(${PROJECT_NAME} SHARED 
    AlwaysXG.cpp
    AllXG.cpp
    AnyXG.cpp
    ContinueXG.cpp
    DelayXG.cpp
    DoneXG.cpp
    FalseXG.cpp
    NoneXG.cpp
    ResumeXG.cpp
    StartXG.cpp
    TrueXG.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC yq_xg)
LinkTest(${PROJECT_NAME})
