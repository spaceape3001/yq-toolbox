////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceStringDriver.hpp>

namespace yq {
    class ResourceXmlInfoer : public ResourceStringInfoer {
    public:
    
        using ResourceStringInfoer::info;
        virtual ResourceInfo* info(const std::string&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfo* info(const XmlDocument&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceXmlInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::xml);
        virtual ~ResourceXmlInfoer();
    };
    
    class ResourceXmlLoader : public ResourceStringLoader {
    public:

        using ResourceStringLoader::load;
        virtual Resource* load(const std::string&, const ResourceLoadAPI&) const override final;
        virtual Resource* load(const XmlDocument&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceXmlLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::xml);
        virtual ~ResourceXmlLoader();
    };

    class ResourceXmlSaver : public ResourceStringSaver {
    public:

        using ResourceStringSaver::save;
        virtual std::error_code  save(const Resource&, std::string&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, XmlDocument&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceXmlSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::xml);
        virtual ~ResourceXmlSaver();
    };
}
