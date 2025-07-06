////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetDriver.hpp>

namespace yq {
    class Asset::UrlInfoer : public Infoer {
    public:
    
        using Infoer::info;
        
    protected:
        UrlInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::url);
        virtual ~UrlInfoer();
    };
    
    class Asset::UrlLoader : public Loader {
    public:
    
        using Loader::load;
        
    protected:
        UrlLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::url);
        virtual ~UrlLoader();
    };

    class Asset::UrlSaver : public Saver {
    public:

        using Saver::save;

    protected:
        UrlSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::url);
        virtual ~UrlSaver();
    };
}
