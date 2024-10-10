################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(CURL REQUIRED)

add_library(yq_network SHARED
    net/ContentType.cpp
    net/Curl.cpp
    net/HttpParser.cpp
    net/HttpStatus.cpp
    net/Url.cpp
    net/VersionSpec.cpp
)

target_include_directories(yq_network
    PRIVATE
        ${CURL_INCLUDE_DIR}
)

target_link_libraries(yq_network 
    PUBLIC
        yq_core

    PRIVATE
        ${CURL_LIBRARIES}
        json
)

LinkTest(yq_network)

