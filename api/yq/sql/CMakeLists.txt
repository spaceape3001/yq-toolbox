################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_sql)

find_package(SQLite3 REQUIRED)

add_library(${PROJECT_NAME} SHARED
    sql.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        yqtoolbox
        ${SQLite3_LIBRARY}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
        ${SQLite3_INCLUDE_DIRS}
)

##########################
##  LINK TEST

LinkTest(${PROJECT_NAME})

