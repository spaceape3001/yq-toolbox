////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceDriverAPI.hpp>
#include <yq/resource/ResourceLogging.hpp>
#include <yq/resource/ResourceStringDriver.hpp>
#include <yq/file/FileUtils.hpp>

namespace yq {
    ///////////////////////////////////

    ResourceStringInfoer::ResourceStringInfoer(const ResourceMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceFileInfoer(meta, exts, sl, type)
    {
    }

    ResourceStringInfoer::~ResourceStringInfoer()
    {
    }
    
    ResourceInfo* ResourceStringInfoer::info(const std::filesystem::path& fp, const ResourceInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            resourceWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::string   str   = file_string(fp);
        return info(str, api);
    }

    ///////////////////////////////////

    ResourceStringLoader::ResourceStringLoader(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceFileLoader(meta, exts, sl, type)
    {
    }
    
    ResourceStringLoader::~ResourceStringLoader()
    {
    }

    Resource* ResourceStringLoader::load(const std::filesystem::path& fp, const ResourceLoadAPI& api) const
    {
        if(!file_exists(fp)){
            resourceWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::string   str   = file_string(fp);
        return load(str, api);
    }

    ///////////////////////////////////

    ResourceStringSaver::ResourceStringSaver(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceFileSaver(meta, exts, sl, type)
    {
    }
    
    ResourceStringSaver::~ResourceStringSaver()
    {
    }

    std::error_code  ResourceStringSaver::save(const Resource&resource, const std::filesystem::path&fp, const ResourceSaveAPI&api) const
    {
        std::string       str;
        std::error_code ec  = save(resource, str, api);
        if(ec != std::error_code())
            return ec;
        
        if(!file_write(fp, str))
            return errors::failed_to_write_file();
        return std::error_code();
    }

    ///////////////////////////////////
}
