################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yqtoolbox)

option(Feature_GLM "Add GLM Bindings" ON)

find_package(CURL REQUIRED)
find_package(Log4cpp REQUIRED)
find_package(TBB REQUIRED)
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
    0/basic/Any.hpp
    0/basic/Any.cpp
    0/basic/BasicApp.hpp
    0/basic/BasicApp.cpp
    0/basic/ContentType.hpp
    0/basic/ContentType.cpp
    0/basic/DelayInit.hpp
    0/basic/DelayInit.cpp
    0/basic/Encode64.hpp
    0/basic/Encode64.cpp
    0/basic/Enum.hpp
    0/basic/Enum.cpp
    0/basic/ErrorDB.hpp
    0/basic/ErrorDB.cpp
    0/basic/Exception.hpp
    0/basic/Exception.hxx
    0/basic/Exception.cpp
    0/basic/Flag.hpp
    0/basic/Flag.cpp
    0/basic/Format.hpp
    0/basic/Format.cpp
    0/basic/Future.cpp
    0/basic/Global.cpp
    0/basic/HttpParser.cpp
    0/basic/HttpStatus.cpp
    0/basic/IgCase.cpp
    0/basic/IterUtf8.cpp
    0/basic/Logging.cpp
    0/basic/MaybeCase.cpp
    0/basic/MD5.cpp
    0/basic/MetaObject.cpp
    0/basic/Object.cpp
    0/basic/Random.cpp
    0/basic/Ref.cpp
    0/basic/RevIgCase.cpp
    0/basic/Revision.cpp
    0/basic/TextUtils.cpp
    0/basic/TextUtils32.cpp
    0/basic/ThreadId.cpp
    0/basic/UniqueID.cpp
    0/basic/Url.hpp
    0/basic/Url.cpp
    0/basic/VersionSpec.cpp
    0/basic/XmlObject.cpp
    0/chemistry/chemistry.cpp
    0/gis/gis.cpp
    0/graph/graph.cpp
    0/graph/xfg/xfg.cpp
    0/io/io.cpp
    0/math/math.cpp
    0/math/meta_coords.cpp
    0/math/meta_general.cpp
    0/math/meta_glm.cpp
    0/math/meta_shapes.cpp
    0/math/meta_tensors.cpp
    0/math/meta_units.cpp
    0/math/meta_vectors.cpp
    0/math/strings.cpp
    0/math/UserExpr.cpp
    0/math/color/HSL.hpp
    0/math/color/HSL.hxx
    0/math/color/HSL.cpp
    0/math/color/HSV.hpp
    0/math/color/HSV.hxx
    0/math/color/HSV.cpp
    0/math/color/RGB.cpp
    0/math/color/RGBA.cpp
    0/meta/meta.cpp
    0/sql/sql.cpp
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
        ${glm_INCLUDE_DIR}
)

LinkTest(${PROJECT_NAME})


