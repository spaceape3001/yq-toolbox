////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceByteDriver.hpp>

namespace yq {
    class ResourceKVTreeInfoer : public ResourceByteInfoer {
    public:
    
        using ResourceByteInfoer::info;
        virtual ResourceInfoPtr info(const ByteArray&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfoPtr info(const KVTree&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceKVTreeInfoer(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, bool, Type type=Type::kvtree);
        virtual ~ResourceKVTreeInfoer();
        
    private:
        unsigned int m_options;
    };
    
    class ResourceKVTreeLoader : public ResourceByteLoader {
    public:

        using ResourceByteLoader::load;
        virtual ResourcePtr load(const ByteArray&, const ResourceLoadAPI&) const override final;
        virtual ResourcePtr load(const KVTree&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceKVTreeLoader(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, bool, Type type=Type::kvtree);
        virtual ~ResourceKVTreeLoader();
    private:
        unsigned int m_options;
    };

    class ResourceKVTreeSaver : public ResourceByteSaver {
    public:

        using ResourceByteSaver::save;
        virtual std::error_code  save(const Resource&, ByteArray&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, KVTree&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceKVTreeSaver(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, Type type=Type::kvtree);
        virtual ~ResourceKVTreeSaver();
    };
}
