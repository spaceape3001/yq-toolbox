################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(core_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yqutility BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

core_test(encode64)
core_test(http)
core_test(strings)
core_test(refs)
core_test(variants)

core_test(fraction)
core_test(units)
core_test(vector1)
core_test(vector2)
core_test(vector3)
core_test(vector4)

core_test(earthdates)


