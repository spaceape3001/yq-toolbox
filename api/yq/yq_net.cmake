################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_net SHARED
    net/ContentType.cpp
    net/HttpParser.cpp
    net/HttpStatus.cpp
    net/Url.cpp
    net/VersionSpec.cpp
)

target_link_libraries(yq_net 
    PUBLIC
        yq_core

    PRIVATE
        yq_json
)

if(Build_CURL)
    target_sources(yq_net 
        PUBLIC 
            net/Curl.cpp
    )

    target_include_directories(yq_net
        PRIVATE
            ${CURL_INCLUDE_DIR}
    )

    message("Adding curl libraries... ${CURL_LIBRARIES}")

    target_link_libraries(yq_net 
        PUBLIC
            ${CURL_LIBRARIES}
    )
endif()

LinkTest(yq_net)

