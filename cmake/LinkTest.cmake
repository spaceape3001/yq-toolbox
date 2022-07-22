################################################################################
##
##  YOUR QUILL
##
################################################################################

MACRO(LinkTest Lib )
    IF(GCC)
        add_executable( lt_${Lib} ${YQ_TOOLBOX_DIR}/cmake/linktest.cpp )
        target_link_libraries(lt_${Lib} ${Lib}) 
        set_target_properties(lt_${Lib} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/linktest )
    ENDIF()
ENDMACRO()

