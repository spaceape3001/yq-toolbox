////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetLibrary.hpp"
#include <yq/asset/AssetLibraryMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::AssetLibrary)

namespace yq {
    AssetLibraryMeta::AssetLibraryMeta(std::string_view zName, AssetMeta& base, const std::source_location& sl) : 
        AssetMeta(zName, base, sl)
    {
        Asset::repo().libraries.push_back(this);
    }

    void AssetLibrary::init_meta()
    {
        auto w = writer<AssetLibrary>();
        w.description("Library of Assets");
    }
    
    AssetLibrary::AssetLibrary()
    {
    }
    
    AssetLibrary::~AssetLibrary()
    {
    }
        
    bool    AssetLibrary::contains(const std::string&k) const
    {
        return m_assets.contains(k);
    }
}
