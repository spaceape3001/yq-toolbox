################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(graph_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_graph BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

graph_test(graph)
