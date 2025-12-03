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

    /*! \brief Collection of resources
    
        A resource library comes is a collection of resources.  (Think zip, archive, or similar collection.)  Note, 
        don't make this recursive, so repackage to make a common library.  (ie, some resource formats, like GLTF, 
        is inherently a library of resources.)
    */
    class ResourceLibrary : public Resource {
        YQ_RESOURCE_META(ResourceLibraryMeta)
        YQ_RESOURCE_INFO(ResourceLibraryInfo)
        YQ_RESOURCE_DECLARE(ResourceLibrary, Resource)
    public:
    
        //! TRUE if the library contains the given key for a resource
        bool    contains(const std::string&) const;
    
        static void init_meta();
        
        //! Returns the *FIRST* resource of the given name
        ResourceCPtr                    resource(key_k, const std::string&) const;
        //! Returns the *FIRST* resource of the given name
        ResourceCPtr                    resource(name_k, const std::string&) const;
        const auto&                     resources() const { return m_resources; }
        std::vector<ResourceCPtr>       resouces(name_k, const std::string&) const;
        
        //! Add resource to the library
        virtual void            add(ResourcePtr);
    
        ResourceLibrary();

        size_t                  data_size() const;

    protected:
        friend class Resource;
        
        virtual ~ResourceLibrary();
        
        virtual void    post_add(ResourcePtr);
        
        std::multimap<std::string,ResourceCPtr,IgCase>  m_byName;
        std::map<std::string,ResourceCPtr,IgCase>       m_byKey;
        std::vector<ResourceCPtr>                       m_resources;
    };
}
