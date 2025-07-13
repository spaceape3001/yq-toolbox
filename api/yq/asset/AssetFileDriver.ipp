////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetFileDriver.hpp"
//#include "FileDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/file/FileUtils.hpp>
#include <yq/errors.hpp>

namespace yq {
    ///////////////////////////////////

    AssetFileInfoer::AssetFileInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        AssetInfoer(meta, exts, sl, type)
    {
    }

    AssetFileInfoer::~AssetFileInfoer()
    {
    }
    
    AssetInfo* AssetFileInfoer::info(const UrlView&url, const AssetInfoAPI&api) const 
    {
        if(url.path.empty()){
            assetWarning << "URL from " << api.spec() << " has no path!";
            return nullptr;
        }
        
        std::filesystem::path fp(url.path);
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        return info(fp, api);
    }

    ///////////////////////////////////

    AssetFileLoader::AssetFileLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        AssetLoader(meta, exts, sl, type)
    {
    }
    
    AssetFileLoader::~AssetFileLoader()
    {
    }

    Asset* AssetFileLoader::load(const UrlView& url, const AssetLoadAPI& api) const
    {
        if(url.path.empty()){
            assetWarning << "URL '" << to_string(api.url()) << "' has no path!";
            return nullptr;
        }
        
        std::filesystem::path fp(url.path);
        if(!file_exists(fp)){
            assetWarning << "URL '" << to_string(api.url()) << "' does not exist!";
            return nullptr;
        }
        
        return load(url, api);
    }

    ///////////////////////////////////

    AssetFileSaver::AssetFileSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        AssetSaver(meta, exts, sl, type)
    {
    }
    
    AssetFileSaver::~AssetFileSaver()
    {
    }

    std::error_code  AssetFileSaver::save(const Asset&asset, const UrlView&url, const AssetSaveAPI&api) const
    {
        if(url.path.empty()){
            assetWarning << "URL '" << to_string(api.url()) << "' has no path!";
            return errors::bad_argument();
        }
        
        std::filesystem::path fp(url.path);
        return save(asset, fp, api);
    }

    ///////////////////////////////////
}
