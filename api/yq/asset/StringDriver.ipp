////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StringDriver.hpp"
#include "StringDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/file/FileUtils.hpp>

namespace yq {
    ///////////////////////////////////

    Asset::StringInfoer::StringInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        FileInfoer(meta, exts, sl, type)
    {
    }

    Asset::StringInfoer::~StringInfoer()
    {
    }
    
    AssetInfo* Asset::StringInfoer::info(const std::filesystem::path& fp, const AssetInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::string   str   = file_string(fp);
        return info(str, api);
    }

    ///////////////////////////////////

    Asset::StringLoader::StringLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        FileLoader(meta, exts, sl, type)
    {
    }
    
    Asset::StringLoader::~StringLoader()
    {
    }

    Asset* Asset::StringLoader::load(const std::filesystem::path& fp, const AssetLoadAPI& api) const
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::string   str   = file_string(fp);
        return load(str, api);
    }

    ///////////////////////////////////

    Asset::StringSaver::StringSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        FileSaver(meta, exts, sl, type)
    {
    }
    
    Asset::StringSaver::~StringSaver()
    {
    }

    std::error_code  Asset::StringSaver::save(const Asset&asset, const std::filesystem::path&fp, const AssetSaveAPI&api) const
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
