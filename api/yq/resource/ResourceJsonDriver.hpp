////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceStringDriver.hpp>

namespace yq {
    class ResourceJsonInfoer : public ResourceStringInfoer {
    public:
    
        using ResourceStringInfoer::info;
        virtual ResourceInfoPtr info(const std::string&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfoPtr info(const json&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceJsonInfoer(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, Type type=Type::json);
        virtual ~ResourceJsonInfoer();
    };
    
    class ResourceJsonLoader : public ResourceStringLoader {
    public:

        using ResourceStringLoader::load;
        virtual ResourcePtr load(const std::string&, const ResourceLoadAPI&) const override final;
        virtual ResourcePtr load(const json&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceJsonLoader(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, Type type=Type::json);
        virtual ~ResourceJsonLoader();
    };

    class ResourceJsonSaver : public ResourceStringSaver {
    public:

        using ResourceStringSaver::save;
        virtual std::error_code  save(const Resource&, std::string&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, json&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceJsonSaver(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, Type type=Type::json);
        virtual ~ResourceJsonSaver();
    };
}
