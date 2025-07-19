////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceInfo.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq {
    template <typename C>
    class ResourceInfoMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(ResourceInfoMeta* resourceInfoPtr) : ObjectMeta::Writer<C>(resourceInfoPtr), m_myMeta(resourceInfoPtr)
        {
        }
        
        Writer(ResourceInfoMeta& resourceInfoRef) : Writer(&resourceInfoRef)
        {
        }
        
        template <typename A>
        Writer& resource()
        {
            if(m_myMeta && Meta::thread_safe_write() && !m_myMeta->m_resource)
                m_myMeta->m_resource   = &meta<A>();
            return *this;
        }
        
    private:
        ResourceInfoMeta* m_myMeta;
    };
}
