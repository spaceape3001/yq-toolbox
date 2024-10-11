################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_process SHARED
    process/Execute.cpp
    process/PidFile.cpp
    process/PluginLoader.cpp
)

target_link_libraries(yq_process 
    PUBLIC
        yq_core 
    PRIVATE
        yq_file
        yq_pstreams
)

LinkTest(yq_process)

