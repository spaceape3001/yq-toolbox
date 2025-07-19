////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceFileDriver.hpp>

namespace yq {
    class ResourceByteInfoer : public ResourceFileInfoer {
    public:
    
        using ResourceFileInfoer::info;
        virtual ResourceInfo* info(const std::filesystem::path&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfo* info(const ByteArray&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceByteInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::byte);
        virtual ~ResourceByteInfoer();
    };
    
    class ResourceByteLoader : public ResourceFileLoader {
    public:

        using ResourceFileLoader::load;
        virtual Resource* load(const std::filesystem::path&, const ResourceLoadAPI&) const override final;
        virtual Resource* load(const ByteArray&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceByteLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::byte);
        virtual ~ResourceByteLoader();
    };

    class ResourceByteSaver : public ResourceFileSaver {
    public:

        using ResourceFileSaver::save;
        virtual std::error_code  save(const Resource&, const std::filesystem::path&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, ByteArray&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceByteSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::byte);
        virtual ~ResourceByteSaver();
    };
}
