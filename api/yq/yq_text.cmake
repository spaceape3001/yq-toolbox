################################################################################
##
##  YOUR QUILL
##
################################################################################

#   As many of the text utilities that we can get... used by the wizard

add_library(yq_text SHARED
    text/text.cpp
)

target_include_directories(yq_text
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
)

LinkTest(yq_text)

