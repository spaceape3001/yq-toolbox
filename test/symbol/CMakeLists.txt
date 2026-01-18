################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(symbol_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_symbol BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

symbol_test(symbol_load)
