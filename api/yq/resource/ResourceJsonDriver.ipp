////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceJsonDriver.hpp>
#include <yq/resource/ResourceLogging.hpp>
#include <yq/resource/ResourceDriverAPI.hpp>

#include <yq/net/json.hpp>

namespace yq {
    ///////////////////////////////////

    ResourceJsonInfoer::ResourceJsonInfoer(const ResourceMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceStringInfoer(meta, exts, sl, type)
    {
    }

    ResourceJsonInfoer::~ResourceJsonInfoer()
    {
    }
    
    ResourceInfoPtr ResourceJsonInfoer::info(const std::string& file, const ResourceInfoAPI&api) const 
    {
        json        j;
        try {
            j   = json::parse( file.data(), file.data()+file.size());
        }
        catch(...)
        {
            resourceError << "Unable to parse json: " << to_string(api.url());
            return {};
        }
        
        return info(j, api);
    }

    ///////////////////////////////////

    ResourceJsonLoader::ResourceJsonLoader(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceStringLoader(meta, exts, sl, type)
    {
    }
    
    ResourceJsonLoader::~ResourceJsonLoader()
    {
    }

    ResourcePtr ResourceJsonLoader::load(const std::string& file, const ResourceLoadAPI& api) const
    {
        json        j;
        try {
            j   = json::parse( file.data(), file.data()+file.size());
        }
        catch(...)
        {
            resourceError << "Unable to parse json: " << to_string(api.url());
            return {};
        }
        
        return load(j, api);
    }

    ///////////////////////////////////

    ResourceJsonSaver::ResourceJsonSaver(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceStringSaver(meta, exts, sl, type)
    {
    }
    
    ResourceJsonSaver::~ResourceJsonSaver()
    {
    }

    std::error_code  ResourceJsonSaver::save(const Resource&resource, std::string& data, const ResourceSaveAPI&api) const
    {
        json    j;
        std::error_code ec = save(resource, j, api);
        if(ec != std::error_code())
            return ec;
        
        ::nlohmann::detail::serializer<json> s(::nlohmann::detail::output_adapter<char>(data), ' ');
        s.dump(j, false, false, 0);
        return std::error_code();
    }

    ///////////////////////////////////
}
