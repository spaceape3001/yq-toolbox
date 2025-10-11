////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/resource/ResourceInfo.hpp>
#include <yq/text/IgCase.hpp>

namespace yq {
    class ResourceLibraryMeta : public ResourceMeta {
    public:
    
        template <typename C> class Writer;

        //! Constructor of resource library info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        ResourceLibraryMeta(std::string_view zName, ResourceMeta& base, const std::source_location& sl=std::source_location::current());
        
        //! Resource types this library can contain (empty implies all)
        const std::vector<const ResourceMeta*>& resources() const { return m_resources; }
    
    private:
        std::vector<const ResourceMeta*>   m_resources;
    };
    
    class ResourceLibraryInfo : public ResourceInfo {
        YQ_OBJECT_DECLARE(ResourceLibraryInfo, ResourceInfo)
    public:
        
    };

    class ResourceLibrary : public Resource {
        YQ_RESOURCE_META(ResourceLibraryMeta)
        YQ_RESOURCE_INFO(ResourceLibraryInfo)
        YQ_RESOURCE_DECLARE(ResourceLibrary, Resource)
    public:
    
        bool    contains(const std::string&) const;
    
        static void init_meta();
        
        ResourceCPtr   resource(const std::string&) const;
        
        void            add(std::string_view, ResourcePtr);
        void            add(ResourcePtr);
    
    protected:
        friend class Resource;
        
        ResourceLibrary();
        virtual ~ResourceLibrary();
        
        std::map<std::string,ResourceCPtr,IgCase>   m_resources;
    };
}
