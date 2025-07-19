////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceFileDriver.hpp>

namespace yq {
    class ResourceStringInfoer : public ResourceFileInfoer {
    public:
    
        using ResourceFileInfoer::info;
        virtual ResourceInfo* info(const std::filesystem::path&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfo* info(const std::string&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceStringInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::string);
        virtual ~ResourceStringInfoer();
    };
    
    class ResourceStringLoader : public ResourceFileLoader {
    public:

        using ResourceFileLoader::load;
        virtual Resource* load(const std::filesystem::path&, const ResourceLoadAPI&) const override final;
        virtual Resource* load(const std::string&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceStringLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::string);
        virtual ~ResourceStringLoader();
    };

    class ResourceStringSaver : public ResourceFileSaver {
    public:

        using ResourceFileSaver::save;
        virtual std::error_code  save(const Resource&, const std::filesystem::path&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, std::string&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceStringSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::string);
        virtual ~ResourceStringSaver();
    };
}
