################################################################################
##
##  YOUR QUILL
##
################################################################################

#   Spatial is meant to be a fast spatial relation capability, so rather than 
#   focusing on lines/rectangles, we focus on objects, like chairs, rooms, windows, etc.

#   SUPERSCRIPTS ⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹ ʰ ᵖ ⁿ ʳ ˢ ᵗ ᵘ ᵛ ʷ ˣ ʸ ᶻ
#   Numbers ① ② ③ ④

add_library(yq_spatial SHARED
    SDocument.cpp
    SObject.cpp
    
    bit/SStringMap.cpp
    bit/ID.cpp
    
    io/b3grammar.cpp
)

target_link_libraries(yq_spatial
    PUBLIC
        yq_color
        yq_core
        yq_math
        yq_xml
)

target_include_directories(yq_spatial
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/..
)

LinkTest(yq_spatial)

