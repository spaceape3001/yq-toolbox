################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_random)

add_library(${PROJECT_NAME} SHARED
    Random.cpp
)

target_link_libraries(${PROJECT_NAME} 
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
)

##########################
##  LINK TEST

LinkTest(${PROJECT_NAME})

