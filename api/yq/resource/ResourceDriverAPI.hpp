////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/resource.hpp>
#include <yq/net/Url.hpp>
#include <yq/resource/ResourceIO.hpp>

namespace yq {

    class ResourceInfoAPI {
    public:
    
        std::string_view            spec() const { return m_spec; }
        const Url&                  url() const { return m_url; }

        bool                        contains(uint32_t) const;
        bool                        contains(const std::string&) const;
    
        const Any&                  operator[](uint32_t) const;
        const Any&                  operator[](const std::string&) const;
    
    private:
        friend class Resource;

        ResourceInfoAPI(const ResourceInfoOptions&);
        ResourceInfoAPI(ResourceInfoOptions&&) = delete;
        ~ResourceInfoAPI();

        const ResourceInfoOptions&     m_options;
        std::string_view            m_spec;
        Url                         m_url;
    };

    class ResourceLoadAPI {
    public:
    
        std::string_view            spec() const { return m_spec; }
        const Url&                  url() const { return m_url; }
    
        bool                        contains(uint32_t) const;
        bool                        contains(const std::string&) const;
    
        const Any&                  operator[](uint32_t) const;
        const Any&                  operator[](const std::string&) const;
        

    private:
        friend class Resource;
        
        ResourceLoadAPI(const ResourceLoadOptions&);
        ResourceLoadAPI(ResourceLoadOptions&&) = delete;
        ~ResourceLoadAPI();
        
        const ResourceLoadOptions&     m_options;
        std::string_view            m_spec;
        Url                         m_url;
    };
    
    
    class ResourceSaveAPI {
    public:
    
        const Url&                  url() const { return m_url; }
        
        bool                        contains(uint32_t) const;
        bool                        contains(const std::string&) const;
    
        const Any&                  operator[](uint32_t) const;
        const Any&                  operator[](const std::string&) const;

        FileCollisionStrategy       collision() const { return m_options.collision; }
        bool                        set_name() const { return m_options.set_name; }
    
    private:
        friend class Resource;
        
        ResourceSaveAPI(const ResourceSaveOptions&);
        ResourceSaveAPI(ResourceSaveOptions&&) = delete;
        ~ResourceSaveAPI();

        const ResourceSaveOptions&     m_options;
        Url                         m_url;
    };

}
