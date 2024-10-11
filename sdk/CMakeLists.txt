add_executable(calc calc.cpp)
target_link_libraries(calc yq_userexpr)

add_executable(easter easter.cpp)
target_link_libraries(easter yq_date)

add_executable(kvtree kvtree.cpp)
target_link_libraries(kvtree yq_keyv)
