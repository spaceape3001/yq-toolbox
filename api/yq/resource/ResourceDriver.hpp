////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/core/ErrorDB.hpp>
#include <yq/typedef/string_vectors.hpp>

namespace yq {

    class ResourceDriver {
        friend class Resource;
    public:
    
        enum class Type : uint8_t {
            none    = 0,
            url,
            file,
            byte,
            stream,
            string,
            xml,
            json,
            kvdoc,
            kvtree
        };
        
        Type                type() const { return m_type; }
        const ResourceMeta&    resource() const { return m_resource; }

        constexpr const string_vector_t& extensions() const { return m_extensions; }
        constexpr const std::source_location& location() const { return m_location; }
        
    protected:
        ResourceDriver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceDriver();
        
    private:
        const ResourceMeta&        m_resource;
        string_vector_t         m_extensions;
        std::source_location    m_location;
        Type                    m_type;
    };

    class ResourceInfoer : public ResourceDriver {
    public:

        virtual ResourceInfoPtr info(const UrlView&, const ResourceInfoAPI&) const = 0;

    protected:
        friend class Resource;
        
        ResourceInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceInfoer();
    };
    
    class ResourceLoader : public ResourceDriver {
    public:

        virtual ResourcePtr load(const UrlView&, const ResourceLoadAPI&) const = 0;

    protected:
        friend class Resource;

        ResourceLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceLoader();
    };

    class ResourceSaver : public ResourceDriver {
    public:
        virtual std::error_code  save(const Resource&, const UrlView&, const ResourceSaveAPI&) const = 0;
        
    protected:
        friend class Resource;

        ResourceSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceSaver();
    };
    
    namespace errors {
        using resource_saving_failed   = error_db::entry<"Unable to save resource">;
    }
}
