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


toolbox_test(any)
toolbox_test(axbox1)
toolbox_test(axbox2)
toolbox_test(axbox3)
toolbox_test(axbox4)
toolbox_test(circle2)
toolbox_test(coord1)
toolbox_test(coord2)
toolbox_test(coord3)
toolbox_test(coord4)
toolbox_test(coord5)
toolbox_test(coord6)
toolbox_test(diffengine)
toolbox_test(encode64)
toolbox_test(fraction)
toolbox_test(futures)
toolbox_test(globals)
toolbox_test(http)
toolbox_test(polygon2)
toolbox_test(polygon3)
toolbox_test(polygon4)
toolbox_test(polyline2)
toolbox_test(polyline3)
toolbox_test(polyline4)
toolbox_test(refs)
toolbox_test(segment1)
toolbox_test(segment2)
toolbox_test(segment3)
toolbox_test(segment4)
toolbox_test(size1)
toolbox_test(size2)
toolbox_test(size3)
toolbox_test(size4)
toolbox_test(sphere3)
toolbox_test(sphere4)
toolbox_test(strings)
toolbox_test(tensor11)
toolbox_test(tensor12)
toolbox_test(tensor13)
toolbox_test(tensor14)
toolbox_test(tensor21)
toolbox_test(tensor22)
toolbox_test(tensor23)
toolbox_test(tensor24)
toolbox_test(tensor31)
toolbox_test(tensor32)
toolbox_test(tensor33)
toolbox_test(tensor34)
toolbox_test(tensor41)
toolbox_test(tensor42)
toolbox_test(tensor43)
toolbox_test(tensor44)
toolbox_test(triangle2)
toolbox_test(triangle3)
toolbox_test(triangle4)
toolbox_test(units)
toolbox_test(userexpr)
toolbox_test(vector1)
toolbox_test(vector2)
toolbox_test(vector3)
toolbox_test(vector4)

toolbox_test(earthdates)


