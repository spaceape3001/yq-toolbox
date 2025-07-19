////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceByteDriver.hpp>

namespace yq {
    class ResourceKVDocumentInfoer : public ResourceByteInfoer {
    public:
    
        using ResourceByteInfoer::info;
        virtual ResourceInfo* info(const ByteArray&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfo* info(const KVDocument&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceKVDocumentInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~ResourceKVDocumentInfoer();
        
    private:
        unsigned int m_options;
    };
    
    class ResourceKVDocumentLoader : public ResourceByteLoader {
    public:

        using ResourceByteLoader::load;
        virtual Resource* load(const ByteArray&, const ResourceLoadAPI&) const override final;
        virtual Resource* load(const KVDocument&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceKVDocumentLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~ResourceKVDocumentLoader();
    private:
        unsigned int m_options;
    };

    class ResourceKVDocumentSaver : public ResourceByteSaver {
    public:

        using ResourceByteSaver::save;
        virtual std::error_code  save(const Resource&, ByteArray&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, KVDocument&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceKVDocumentSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::kvdoc);
        virtual ~ResourceKVDocumentSaver();
    };
}
