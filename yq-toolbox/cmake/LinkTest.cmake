################################################################################
##
##  YOUR QUILL
##
################################################################################

MACRO(LinkTest Lib )
    IF(GCC)
        add_executable( lt_${Lib} ${CMAKE_SOURCE_DIR}/yq-toolbox/cmake/linktest.cpp )
        target_link_libraries(lt_${Lib} ${Lib}) 
        set_target_properties(lt_${Lib} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/linktest )
    ENDIF()
ENDMACRO()

