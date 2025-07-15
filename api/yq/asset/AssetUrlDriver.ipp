////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetUrlDriver.hpp>
//#include "UrlDriver.hxx"

namespace yq {
    ///////////////////////////////////

    AssetUrlInfoer::AssetUrlInfoer(const AssetMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        AssetInfoer(meta, exts, sl, type)
    {
    }

    AssetUrlInfoer::~AssetUrlInfoer()
    {
    }
    
    ///////////////////////////////////

    AssetUrlLoader::AssetUrlLoader(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        AssetLoader(meta, exts, sl, type)
    {
    }
    
    AssetUrlLoader::~AssetUrlLoader()
    {
    }

    ///////////////////////////////////

    AssetUrlSaver::AssetUrlSaver(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        AssetSaver(meta, exts, sl, type)
    {
    }
    
    AssetUrlSaver::~AssetUrlSaver()
    {
    }

    ///////////////////////////////////
}
