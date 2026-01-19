////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceFileDriver.hpp"
//#include "FileDriver.hxx"
#include "ResourceLogging.hpp"
#include "ResourceDriverAPI.hpp"

#include <yq/file/FileUtils.hpp>
#include <yq/errors.hpp>

namespace yq {
    ///////////////////////////////////

    ResourceFileInfoer::ResourceFileInfoer(const ResourceMeta& meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) :
        ResourceInfoer(meta, spec, sl, type)
    {
    }

    ResourceFileInfoer::~ResourceFileInfoer()
    {
    }
    
    ResourceInfoPtr ResourceFileInfoer::info(const UrlView&url, const ResourceInfoAPI&api) const 
    {
        if(url.path.empty()){
            resourceWarning << "URL from " << api.spec() << " has no path!";
            return {};
        }
        
        std::filesystem::path fp(url.path);
        if(!file_exists(fp)){
            resourceWarning << "URL's file from " << api.spec() << " does not exist!";
            return {};
        }
        
        return info(fp, api);
    }

    ///////////////////////////////////

    ResourceFileLoader::ResourceFileLoader(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceLoader(meta, spec, sl, type)
    {
    }
    
    ResourceFileLoader::~ResourceFileLoader()
    {
    }

    ResourcePtr ResourceFileLoader::load(const UrlView& url, const ResourceLoadAPI& api) const
    {
        if(url.path.empty()){
            resourceWarning << "URL '" << to_string(api.url()) << "' has no path!";
            return {};
        }
        
        std::filesystem::path fp(url.path);
        if(!file_exists(fp)){
            resourceWarning << "URL '" << to_string(api.url()) << "' does not exist!";
            return {};
        }
        
        return load(fp, api);
    }

    ///////////////////////////////////

    ResourceFileSaver::ResourceFileSaver(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceSaver(meta, spec, sl, type)
    {
    }
    
    ResourceFileSaver::~ResourceFileSaver()
    {
    }

    std::error_code  ResourceFileSaver::save(const Resource&resource, const UrlView&url, const ResourceSaveAPI&api) const
    {
        if(url.path.empty()){
            resourceWarning << "URL '" << to_string(api.url()) << "' has no path!";
            return errors::bad_argument();
        }
        
        std::filesystem::path fp(url.path);
        return save(resource, fp, api);
    }

    ///////////////////////////////////
}
