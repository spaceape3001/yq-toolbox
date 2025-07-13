////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetDriver.hpp>

namespace yq {
    class AssetUrlInfoer : public AssetInfoer {
    public:
    
        using AssetInfoer::info;
        
    protected:
        AssetUrlInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::url);
        virtual ~AssetUrlInfoer();
    };
    
    class AssetUrlLoader : public AssetLoader {
    public:
    
        using AssetLoader::load;
        
    protected:
        AssetUrlLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::url);
        virtual ~AssetUrlLoader();
    };

    class AssetUrlSaver : public AssetSaver {
    public:

        using AssetSaver::save;

    protected:
        AssetUrlSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::url);
        virtual ~AssetUrlSaver();
    };
}
