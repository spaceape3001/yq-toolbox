################################################################################
##
##  YOUR QUILL
##
################################################################################

add_subdirectory(core)
add_subdirectory(date)
add_subdirectory(math)
add_subdirectory(userexpr)

if(0)
macro(toolbox_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_core BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()


toolbox_test(http)


add_executable(test_earthdates earthdates.cpp)
target_link_libraries(test_earthdates PRIVATE yqtoolbox yq_date BoostUT)
add_test(NAME earthdates COMMAND test_earthdates)


endif()
