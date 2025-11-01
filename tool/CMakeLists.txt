################################################################################
##
##  YOUR QUILL
##
################################################################################

add_executable(xmlread xmlread.cpp)
target_link_libraries(xmlread yq_rapidxml)

if(Build_ASIO)
    add_executable(tcpsink tcpsink.cpp)
    target_link_libraries(tcpsink yq_asio)

    # add_executable(udpsink udpsink.cpp)
    # target_link_libraries(udpsink asio)
endif()

if(Build_CURL)
    add_executable(ask ask.cpp)
    target_link_libraries(ask ${CURL_LIBRARIES})
endif()


if(Build_SQL)
    add_executable(sqlquery sqlquery.cpp)
    target_link_libraries(sqlquery yq_sql)
endif()
