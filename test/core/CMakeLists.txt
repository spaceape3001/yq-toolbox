################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_core BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

test(any)
test(diffengine)
test(encode64)
test(futures)
test(globals)
test(memory)
test(refs)
test(strings)
