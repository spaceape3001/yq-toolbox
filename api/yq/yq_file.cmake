################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_file SHARED
    file/AbstractFile.cpp
    file/DirUtils.cpp
    file/FileResolver.cpp
    file/FileUtils.cpp
    
    stream/OSFile.cpp
)

target_link_libraries(yq_file PUBLIC
    yq_core
)

LinkTest(yq_file)

