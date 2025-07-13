////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetDriverAPI.hpp>
#include <yq/asset/AssetLogging.hpp>
#include <yq/asset/AssetStringDriver.hpp>
#include <yq/file/FileUtils.hpp>

namespace yq {
    ///////////////////////////////////

    AssetStringInfoer::AssetStringInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        AssetFileInfoer(meta, exts, sl, type)
    {
    }

    AssetStringInfoer::~AssetStringInfoer()
    {
    }
    
    AssetInfo* AssetStringInfoer::info(const std::filesystem::path& fp, const AssetInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::string   str   = file_string(fp);
        return info(str, api);
    }

    ///////////////////////////////////

    AssetStringLoader::AssetStringLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        AssetFileLoader(meta, exts, sl, type)
    {
    }
    
    AssetStringLoader::~AssetStringLoader()
    {
    }

    Asset* AssetStringLoader::load(const std::filesystem::path& fp, const AssetLoadAPI& api) const
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::string   str   = file_string(fp);
        return load(str, api);
    }

    ///////////////////////////////////

    AssetStringSaver::AssetStringSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        AssetFileSaver(meta, exts, sl, type)
    {
    }
    
    AssetStringSaver::~AssetStringSaver()
    {
    }

    std::error_code  AssetStringSaver::save(const Asset&asset, const std::filesystem::path&fp, const AssetSaveAPI&api) const
    {
        std::string       str;
        std::error_code ec  = save(asset, str, api);
        if(ec != std::error_code())
            return ec;
        
        if(!file_write(fp, str))
            return errors::failed_to_write_file();
        return std::error_code();
    }

    ///////////////////////////////////
}
