////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceLibrary.hpp>
#include <yq/resource/ResourceMetaWriter.hpp>

namespace yq {
    template <typename C>
    class ResourceLibraryMeta::Writer : public ResourceMeta::Writer<C> {
    public:
        Writer(ResourceLibraryMeta* resourceInfoPtr) : ResourceMeta::Writer<C>(resourceInfoPtr), m_myMeta(resourceInfoPtr)
        {
        }
        
        Writer(ResourceLibraryMeta& resourceInfoRef) : Writer(&resourceInfoRef)
        {
        }
        
        template <SomeResource A>
        Writer& resource()
        {
            if(m_myMeta && thread_safe_write()){
                m_myMeta -> m_resources.push_back(&meta<A>());
            }
        
            return *this;
        }
        
    private:
        ResourceLibraryMeta* m_myMeta;
    };
}
