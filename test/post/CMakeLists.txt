################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_post BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

test(posting)
test(pbx)
test(triggers)
