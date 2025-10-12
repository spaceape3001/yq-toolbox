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

    void        ResourceLibrary::add(ResourcePtr ap)
    {
        if(!ap)
            return;

        if(ap->m_name.empty()){
            std::string_view    tn  = ap->metaInfo().stem();
            for(size_t i = 1; m_byName.contains(ap->m_name = std::format("{}_{}", tn, i)); ++i)
                ;
        }

        if(ap->url().empty()){
            Url u2      = url();
            u2.fragment = ap->m_name;
            ap->m_url   = u2;
        }
        m_byName[ap->m_name] = (ResourceCPtr) ap;
        m_resources.push_back(ap);
        post_add(ap);
    }


    bool        ResourceLibrary::contains(const std::string&k) const
    {
        return m_byName.contains(k);
    }

    size_t         ResourceLibrary::data_size() const
    {
        size_t  cnt = 0;
        for(auto& itr : m_resources)
            if(itr)
                cnt += itr->data_size();
        return cnt;
    }

    void        ResourceLibrary::post_add(ResourcePtr ap)
    {
    }
        
    ResourceCPtr   ResourceLibrary::resource(const std::string& k) const
    {
        auto x = m_byName.find(k);
        if(x == m_byName.end())
            return {};
        return x->second;
    }
}
