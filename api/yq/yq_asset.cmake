################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_asset SHARED
    asset/Asset.cpp
    asset/AssetCache.cpp
    asset/AssetFactory.cpp
    #asset/AssetLibrary.cpp
)

target_link_libraries(yq_asset 
    PUBLIC
        yq_core 
    PRIVATE
        yq_file
)

LinkTest(yq_asset)

