////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceDriver.hpp>

namespace yq {
    class ResourceUrlInfoer : public ResourceInfoer {
    public:
    
        using ResourceInfoer::info;
        
    protected:
        ResourceUrlInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::url);
        virtual ~ResourceUrlInfoer();
    };
    
    class ResourceUrlLoader : public ResourceLoader {
    public:
    
        using ResourceLoader::load;
        
    protected:
        ResourceUrlLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::url);
        virtual ~ResourceUrlLoader();
    };

    class ResourceUrlSaver : public ResourceSaver {
    public:

        using ResourceSaver::save;

    protected:
        ResourceUrlSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::url);
        virtual ~ResourceUrlSaver();
    };
}
