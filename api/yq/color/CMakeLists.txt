project(yq_color)

add_library(${PROJECT_NAME} SHARED
    color.cpp
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

