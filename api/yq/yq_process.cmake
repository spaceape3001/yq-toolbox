################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_process SHARED
    process/Execute.cpp
    process/PidFile.cpp
    process/PluginLoader.cpp
    process/Settings.cpp
)

target_link_libraries(yq_process 
    PUBLIC
        yq_core 
        yq_file
    PRIVATE
        yq_pstreams
)

LinkTest(yq_process)

