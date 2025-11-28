////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceLibrary.hpp"
#include <yq/core/Logging.hpp>
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

        if(ap->m_key.empty()){
            std::string_view    tn  = ap->metaInfo().stem();
            for(size_t i = 1; m_byKey.contains(ap->m_key = std::format("{}_{}", tn, i)); ++i)
                ;
        }

        if(ap->url().empty()){
            ap -> m_url             = url();
            ap -> m_url.fragment    = ap->m_key;
        }
        m_byKey[ap->m_key]         = (ResourceCPtr) ap;
        m_byName.insert({ap->m_name, (ResourceCPtr) ap});
        m_resources.push_back(ap);
        post_add(ap);
    }


    bool        ResourceLibrary::contains(const std::string&k) const
    {
        return m_byKey.contains(k);
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
        
    ResourceCPtr   ResourceLibrary::resource(key_k, const std::string& k) const
    {
        auto x = m_byKey.find(k);
        if(x == m_byKey.end())
            return {};
        return x->second;
    }

    ResourceCPtr   ResourceLibrary::resource(name_k, const std::string& k) const
    {
        auto x = m_byName.find(k);
        if(x == m_byName.end())
            return {};
        return x->second;
    }

    std::vector<ResourceCPtr>   ResourceLibrary::resouces(name_k, const std::string& k) const
    {
        std::vector<ResourceCPtr>   ret;
        auto x = m_byName.equal_range(k);
        for(auto i = x.first; i != x.second; ++i)
            ret.push_back(i->second);
        return ret;
    }
}
