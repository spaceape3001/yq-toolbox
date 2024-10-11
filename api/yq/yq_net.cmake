################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(CURL REQUIRED)

add_library(yq_net SHARED
    net/ContentType.cpp
    net/Curl.cpp
    net/HttpParser.cpp
    net/HttpStatus.cpp
    net/Url.cpp
    net/VersionSpec.cpp
)

target_include_directories(yq_net
    PRIVATE
        ${CURL_INCLUDE_DIR}
)

target_link_libraries(yq_net 
    PUBLIC
        yq_core

    PRIVATE
        ${CURL_LIBRARIES}
        yq_json
)

LinkTest(yq_net)

