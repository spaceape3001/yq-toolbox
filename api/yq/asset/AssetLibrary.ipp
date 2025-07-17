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

    void        AssetLibrary::add(std::string_view k, AssetPtr ap)
    {
        if(!ap)
            return;
            
        Url u2  = url();
        u2.fragment = std::string(k);
        ap->m_url   = u2;
        m_assets[u2.fragment] = (AssetCPtr) ap;
    }
        
    AssetCPtr   AssetLibrary::asset(const std::string& k) const
    {
        auto x = m_assets.find(k);
        if(x == m_assets.end())
            return {};
        return x->second;
    }

    bool    AssetLibrary::contains(const std::string&k) const
    {
        return m_assets.contains(k);
    }
}
