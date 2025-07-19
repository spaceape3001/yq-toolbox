////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/resource.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/net/Url.hpp>

namespace yq {
    class ResourceInfoMeta : public ObjectMeta {
    public:
        template <typename> class Writer;
        
        //! Constructor of resource info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        ResourceInfoMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());

        const ResourceInfo*        resource() const { return m_resource; }
        
    private:
        const ResourceInfo*        m_resource = nullptr;
    };
    

    //! Meant to be a *LIGHTWEIGHT* container for getting information about an resource.
    class ResourceInfo : public Object, public RefCount {
        YQ_OBJECT_META(ResourceInfoMeta)
        YQ_OBJECT_DECLARE(ResourceInfo, Object)
    public:
        
        const Url&  url() const { return m_url; }
        
        //! Estimated data size (error on overcounting if unsure)
        size_t      bytes() const { return m_bytes; }

        static void init_meta();
        
        //! ID of the resource (if loaded), zero otherwise
        uint64_t    id() const { return m_id; }
    
        ResourceInfo();
        virtual ~ResourceInfo();
    
    private:
        Url                 m_url;
        size_t              m_bytes  = SIZE_MAX;
        uint64_t            m_id        = 0;
    };
}
