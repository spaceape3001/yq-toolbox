add_executable(calc calc.cpp)
target_link_libraries(calc yqtoolbox)

add_executable(easter easter.cpp)
target_link_libraries(easter yqtoolbox yq_date)

add_executable(kvtree kvtree.cpp)
target_link_libraries(kvtree yqtoolbox)

add_executable(sqlquery sqlquery.cpp)
target_link_libraries(sqlquery yqtoolbox yq_sql)
