################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_symbol SHARED
    symbol/symbol.cpp
    symbol/SymLibLoader.cpp
    symbol/SymSVGExporter.cpp
)

target_link_libraries(yq_symbol
PUBLIC 
    yq_core 
    yq_color 
    yq_math 
    yq_resource
    yq_b3fmt
    yq_xml
)

LinkTest(yq_symbol)

