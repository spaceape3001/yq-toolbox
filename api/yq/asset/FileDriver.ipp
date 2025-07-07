////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "FileDriver.hpp"
#include "FileDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/file/FileUtils.hpp>
#include <yq/errors.hpp>

namespace yq {
    ///////////////////////////////////

    Asset::FileInfoer::FileInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        Infoer(meta, exts, sl, type)
    {
    }

    Asset::FileInfoer::~FileInfoer()
    {
    }
    
    AssetInfo* Asset::FileInfoer::info(const UrlView&url, const AssetInfoAPI&api) const 
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

    Asset::FileLoader::FileLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        Loader(meta, exts, sl, type)
    {
    }
    
    Asset::FileLoader::~FileLoader()
    {
    }

    Asset* Asset::FileLoader::load(const UrlView& url, const AssetLoadAPI& api) const
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

    Asset::FileSaver::FileSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        Saver(meta, exts, sl, type)
    {
    }
    
    Asset::FileSaver::~FileSaver()
    {
    }

    std::error_code  Asset::FileSaver::save(const Asset&asset, const UrlView&url, const AssetSaveAPI&api) const
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
