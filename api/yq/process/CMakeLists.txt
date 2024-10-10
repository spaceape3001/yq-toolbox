################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_process)

add_library(${PROJECT_NAME} SHARED
    Execute.cpp
    PidFile.cpp
    PluginLoader.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        yq_file
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

