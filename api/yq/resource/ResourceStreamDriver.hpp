////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceFileDriver.hpp>
#include <iosfwd>

namespace yq {
    class ResourceStreamInfoer : public ResourceFileInfoer {
    public:
    
        using ResourceFileInfoer::info;
        virtual ResourceInfoPtr info(const std::filesystem::path&, const ResourceInfoAPI&) const override final;
        virtual ResourceInfoPtr info(std::istream&, const ResourceInfoAPI&) const = 0;
        
    protected:
        ResourceStreamInfoer(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, Type type=Type::stream);
        virtual ~ResourceStreamInfoer();
        
    private:
        bool m_binary;
    };
    
    class ResourceStreamLoader : public ResourceFileLoader {
    public:

        using ResourceFileLoader::load;
        virtual ResourcePtr load(const std::filesystem::path&, const ResourceLoadAPI&) const override final;
        virtual ResourcePtr load(std::istream&, const ResourceLoadAPI&) const = 0;
        
    protected:
        ResourceStreamLoader(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, Type type=Type::stream);
        virtual ~ResourceStreamLoader();
        
    private:
        bool m_binary;
    };

    class ResourceStreamSaver : public ResourceFileSaver {
    public:

        using ResourceFileSaver::save;
        virtual std::error_code  save(const Resource&, const std::filesystem::path&, const ResourceSaveAPI&) const override final;
        virtual std::error_code  save(const Resource&, std::ostream&, const ResourceSaveAPI&) const = 0;

    protected:
        ResourceStreamSaver(const ResourceMeta&, const ResourceIOSpec& spec, const std::source_location&, Type type=Type::stream);
        virtual ~ResourceStreamSaver();
        
    private:
        bool m_binary;
    };
}
