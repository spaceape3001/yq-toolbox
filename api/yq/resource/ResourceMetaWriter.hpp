////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq {
    template <typename C>
    class ResourceMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(ResourceMeta* resourceInfoPtr) : ObjectMeta::Writer<C>(resourceInfoPtr)
        {
        }
        
        Writer(ResourceMeta& resourceInfoRef) : Writer(&resourceInfoRef)
        {
        }
    };

    template <typename C> 
    class ResourceFixer : public ObjectFixer<C> {
    public:
    
        ResourceFixer(std::string_view zName, typename C::MyBase::MyMeta& base, const std::source_location& sl=std::source_location::current()) : 
            ObjectFixer<C>(zName, base, sl)
        {
        }
        
        virtual ResourceInfo*  createInfo() const 
        { 
            return new typename C::MyInfo; 
        }
        
        virtual void        sweep_impl()
        {
            ObjectFixer<C>::sweep_impl();
            auto w = writer<typename C::MyInfo>();
            w.template resource<C>();
        }
    };
}
