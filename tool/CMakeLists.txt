find_package(CURL REQUIRED)

add_executable(ask ask.cpp)
target_link_libraries(ask ${CURL_LIBRARIES})

add_executable(xmlread xmlread.cpp)
target_link_libraries(xmlread RapidXml)


