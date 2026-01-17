################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(b3fmt_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_b3fmt BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

b3fmt_test(b3parse)
#doodle_test(evaluator)
