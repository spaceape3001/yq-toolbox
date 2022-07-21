################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yqutility)

find_package(CURL REQUIRED)
find_package(Log4cpp REQUIRED)
find_package(TBB REQUIRED)
find_package(glm REQUIRED)
find_package(SQLite3 REQUIRED)

message("INCLUDE ${Sqlite3_INCLUDE_DIRS}")


#   This is a testing file, excluded from GIT, used for quick test compilation 
#   of code before sliding it into the appropriate spot of the build.
#   (ie.  prototyping goes here, but do not commit/push test.cpp.)
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test.cpp)
    set(core_test_source ./test.cpp)
endif()

add_library(${PROJECT_NAME} SHARED 
    ${core_test_source}
    ./basic/basic.cpp
    ./chemistry/chemistry.cpp
    ./earth/earth.cpp
    ./math/math.cpp
    ./physics/physics.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        YQ__CORE__OVERRIDE 
)

IF(GCC)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            stdc++fs
    )
ENDIF()

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${LOG4CPP_LIBRARIES} 
        ${TBB_LIBRARIES}
        ${CURL_LIBRARIES}
        ${SQLite3_LIBRARY}
        pstreams
        RapidXml
        json
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${TBB_INCLUDE_DIR}
        ${LOG4CPP_INCLUDE_DIR}
        ${Sqlite3_INCLUDE_DIRS}
)

LinkTest(${PROJECT_NAME})


