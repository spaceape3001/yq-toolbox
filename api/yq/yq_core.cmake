################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_core SHARED
    strings.cpp

    container/ByteArray.cpp

    core/DelayInit.cpp
    core/ErrorDB.cpp
    core/Future.cpp
    core/Ref.cpp
    core/ThreadId.cpp
    
    hash/MD5.cpp
    
    text/basic.cpp
    text/basic32.cpp
    text/chars.cpp
    text/chars32.cpp
    text/copy.cpp
    text/copy32.cpp
    text/count.cpp
    text/count32.cpp
    text/Encode64.cpp
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
    text/misc.cpp
    text/misc32.cpp
    text/parse.cpp
    text/parse32.cpp
    text/RevIgCase.cpp
    text/split.cpp
    text/split32.cpp
    text/transform.cpp
    text/transform32.cpp
)

target_include_directories(yq_core
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
)

LinkTest(yq_core)

