project(yqgraphics)

add_library(${PROJECT_NAME} SHARED
    pixel/Pixmap.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        yqtoolbox
)

##########################
##  LINK TEST

LinkTest(${PROJECT_NAME})

