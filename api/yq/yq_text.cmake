################################################################################
##
##  YOUR QUILL
##
################################################################################

#   As many of the text utilities that we can get... used by the wizard

add_library(yq_text SHARED
    text/basic.cpp
    text/basic32.cpp
    text/chars.cpp
    text/chars32.cpp
    text/copy.cpp
    text/copy32.cpp
    text/count.cpp
    text/count32.cpp
    text/format.cpp
    text/format32.cpp
    text/IgCase.cpp
    text/ios.cpp
    text/ios32.cpp
    text/IterUtf8.cpp
    text/join.cpp
    text/join32.cpp
    text/match.cpp
    text/match32.cpp
    text/MaybeCase.cpp
    text/RevIgCase.cpp
    text/split.cpp
    text/split32.cpp
    text/transform.cpp
    text/transform32.cpp
)

target_include_directories(yq_text
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
)

LinkTest(yq_text)

