////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ByteDriver.hpp"
#include "ByteDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/container/ByteArray.hpp>
#include <yq/file/FileUtils.hpp>

namespace yq {
    ///////////////////////////////////

    Asset::ByteInfoer::ByteInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        FileInfoer(meta, exts, sl, type)
    {
    }

    Asset::ByteInfoer::~ByteInfoer()
    {
    }
    
    AssetInfo* Asset::ByteInfoer::info(const std::filesystem::path& fp, const AssetInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        return info(bytes, api);
    }

    ///////////////////////////////////

    Asset::ByteLoader::ByteLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        FileLoader(meta, exts, sl, type)
    {
    }
    
    Asset::ByteLoader::~ByteLoader()
    {
    }

    Asset* Asset::ByteLoader::load(const std::filesystem::path& fp, const AssetLoadAPI& api) const
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        return load(bytes, api);
    }

    ///////////////////////////////////

    Asset::ByteSaver::ByteSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        FileSaver(meta, exts, sl, type)
    {
    }
    
    Asset::ByteSaver::~ByteSaver()
    {
    }

    std::error_code  Asset::ByteSaver::save(const Asset&asset, const std::filesystem::path&fp, const AssetSaveAPI&api) const
    {
        ByteArray       bytes;
        std::error_code ec  = save(asset, bytes, api);
        if(ec != std::error_code())
            return ec;
        
        if(!file_write(fp, bytes))
            return errors::failed_to_write_file();
        return std::error_code();
    }

    ///////////////////////////////////
}
