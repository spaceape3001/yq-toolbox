project(yq_userexpr)

add_library(${PROJECT_NAME} SHARED
    userexpr.cpp
    impl/impl.cpp
    opcode/opcode.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        yqtoolbox
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
)

##########################
##  LINK TEST

LinkTest(${PROJECT_NAME})

