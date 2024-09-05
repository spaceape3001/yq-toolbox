################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yqtoolbox)

set(TOOLBOX_API_DIR ${CMAKE_CURRENT_LIST_DIR})
set(TOOLBOX_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(yq)


find_package(CURL REQUIRED)
if(Feature_GLM)
    find_package(glm REQUIRED)
endif()
find_package(SQLite3 REQUIRED)


#   This is a testing file, excluded from GIT, used for quick test compilation 
#   of code before sliding it into the appropriate spot of the build.
#   (ie.  prototyping goes here, but do not commit/push test.cpp.)
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test.cpp)
    set(core_test_source ./test.cpp)
endif()

add_library(${PROJECT_NAME} SHARED 
    ${core_test_source}
    0/chemistry/chemistry.cpp
    0/gis/gis.cpp
    0/graph/graph.cpp
    0/graph/xfg/xfg.cpp
    0/math/Pose2.hpp
    0/math/Pose2.hxx
    0/math/Pose2.cpp
    0/math/Pose3.hpp
    0/math/Pose3.hxx
    0/math/Pose3.cpp
    0/math/SimpleSpace.hpp
    0/math/SimpleSpace.cpp
    0/math/meta_coords.cpp
    0/math/meta_general.cpp
    0/math/meta_glm.cpp
    0/physics/physics.cpp
)

if(Feature_GLM)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
            YQ_FEATURE_GLM=1
    )
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        YQ__CORE__OVERRIDE 
)

IF(GCC)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            stdc++fs
            stdc++exp
    )
ENDIF()

message("Log4cpp libraries... ${LOG4CPP_LIBRARIES}")

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${LOG4CPP_LIBRARIES} 
        ${TBB_LIBRARIES}
        ${CURL_LIBRARIES}
        ${SQLite3_LIBRARY}
        RapidXml
        json
        tbbmalloc_proxy
        yqtoolbox2
        
     PRIVATE
        pstreams
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${TBB_INCLUDE_DIR}
        ${LOG4CPP_INCLUDE_DIR}
        ${SQLite3_INCLUDE_DIRS}
)


LinkTest(${PROJECT_NAME})


