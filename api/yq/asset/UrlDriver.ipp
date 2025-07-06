////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UrlDriver.hpp"
#include "UrlDriver.hxx"

namespace yq {
    ///////////////////////////////////

    Asset::UrlInfoer::UrlInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        Infoer(meta, exts, sl, type)
    {
    }

    Asset::UrlInfoer::~UrlInfoer()
    {
    }
    
    ///////////////////////////////////

    Asset::UrlLoader::UrlLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        Loader(meta, exts, sl, type)
    {
    }
    
    Asset::UrlLoader::~UrlLoader()
    {
    }

    ///////////////////////////////////

    Asset::UrlSaver::UrlSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        Saver(meta, exts, sl, type)
    {
    }
    
    Asset::UrlSaver::~UrlSaver()
    {
    }

    ///////////////////////////////////
}
