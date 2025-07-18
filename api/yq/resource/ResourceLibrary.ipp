////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceLibrary.hpp"
#include <yq/resource/ResourceLibraryMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::ResourceLibrary)

namespace yq {
    ResourceLibraryMeta::ResourceLibraryMeta(std::string_view zName, ResourceMeta& base, const std::source_location& sl) : 
        ResourceMeta(zName, base, sl)
    {
        Resource::repo().libraries.push_back(this);
    }

    void ResourceLibrary::init_meta()
    {
        auto w = writer<ResourceLibrary>();
        w.description("Library of Resources");
    }
    
    ResourceLibrary::ResourceLibrary()
    {
    }
    
    ResourceLibrary::~ResourceLibrary()
    {
    }

    void        ResourceLibrary::add(std::string_view k, ResourcePtr ap)
    {
        if(!ap)
            return;
            
        Url u2  = url();
        u2.fragment = std::string(k);
        ap->m_url   = u2;
        m_resources[u2.fragment] = (ResourceCPtr) ap;
    }
        
    ResourceCPtr   ResourceLibrary::resource(const std::string& k) const
    {
        auto x = m_resources.find(k);
        if(x == m_resources.end())
            return {};
        return x->second;
    }

    bool    ResourceLibrary::contains(const std::string&k) const
    {
        return m_resources.contains(k);
    }
}
