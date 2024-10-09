project(yq_pixel)

add_library(${PROJECT_NAME} SHARED
    Painter.cpp
    Pixmap.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        yqtoolbox
)

##########################
##  LINK TEST

LinkTest(${PROJECT_NAME})

