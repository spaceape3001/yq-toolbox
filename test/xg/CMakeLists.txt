################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(xg_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_xg BoostUT ${ARGN})
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

xg_test(xgruntime yq_process)
