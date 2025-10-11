////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceDriver.hpp>

namespace yq {
    class ResourceFileInfoer : public ResourceInfoer {
    public:
    
        virtual ResourceInfoPtr info(const UrlView&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfoPtr info(const std::filesystem::path&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceFileInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::file);
        virtual ~ResourceFileInfoer();
    };
    
    class ResourceFileLoader : public ResourceLoader {
    public:
    
        virtual ResourcePtr load(const UrlView&, const ResourceLoadAPI&) const override final;
        virtual ResourcePtr load(const std::filesystem::path&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceFileLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::file);
        virtual ~ResourceFileLoader();
    };

    class ResourceFileSaver : public ResourceSaver {
    public:

        virtual std::error_code  save(const Resource&, const UrlView&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, const std::filesystem::path&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceFileSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::file);
        virtual ~ResourceFileSaver();
    };
}
