project(yqtoolbox)

option(Feature_GLM "Add GLM Bindings" ON)

if(Feature_GLM)
    find_package(glm REQUIRED)
endif()

find_package(Log4cpp REQUIRED)
find_package(TBB REQUIRED)
find_package(CURL REQUIRED)

#   This is a testing file, excluded from GIT, used for quick test compilation 
#   of code before sliding it into the appropriate spot of the build.
#   (ie.  prototyping goes here, but do not commit/push test.cpp.)
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test.cpp)
    set(core_test_source ./test.cpp)
endif()

#   Headers are being listed for anybody using an IDE (unnecessary for pure commandline)

add_library(${PROJECT_NAME} SHARED
    ${core_test_source}

    strings.cpp
    units.cpp

    basic/basic.cpp
    basic/MD5.cpp

    container/container.cpp
    coord/coord.cpp

    #   Rest of graph to come
    
    math/math.cpp
    meta/meta.cpp
    
    shape/shape.cpp
    tensor/tensor.cpp
    text/text.cpp
    unit/Dimension.cpp
    vector/vector.cpp
)

##########################
##  COMPILER DEFINITIONS

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        YQ__CORE__OVERRIDE 
)

if(Feature_GLM)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
            #   These have been mixed/scattered, use both
            YQ_FEATURE_GLM=1
            YQ_USE_GLM=1
    )
endif()

##########################
##  INCLUDE DIRECTORIES

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
        ${TBB_INCLUDE_DIR}
        ${LOG4CPP_INCLUDE_DIR}
)

if(Feature_GLM)
    target_include_directories(${PROJECT_NAME} INTERFACE
        ${glm_INCLUDE_DIR}
    )
endif()


##########################
##  OTHER LIBRARIES

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        ${LOG4CPP_LIBRARIES} 
        ${TBB_LIBRARIES}
        ${CURL_LIBRARIES}

        json
        RapidXml
        tbbmalloc_proxy

        PRIVATE
            pstreams
)

IF(GCC)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            stdc++fs
            stdc++exp
    )
ENDIF()

##########################
##  LINK TEST

LinkTest(${PROJECT_NAME})

