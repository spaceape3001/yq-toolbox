################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(toolbox_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yqtoolbox BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

toolbox_test(encode64)
toolbox_test(http)
toolbox_test(strings)
toolbox_test(refs)
toolbox_test(variants)

toolbox_test(fraction)
toolbox_test(units)
toolbox_test(vector1)
toolbox_test(vector2)
toolbox_test(vector3)
toolbox_test(vector4)

toolbox_test(earthdates)


