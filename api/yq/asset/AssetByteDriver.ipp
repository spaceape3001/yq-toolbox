////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssetByteDriver.hpp"
//#include "ByteDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/container/ByteArray.hpp>
#include <yq/file/FileUtils.hpp>

namespace yq {
    ///////////////////////////////////

    AssetByteInfoer::AssetByteInfoer(const AssetMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        AssetFileInfoer(meta, exts, sl, type)
    {
    }

    AssetByteInfoer::~AssetByteInfoer()
    {
    }
    
    AssetInfo* AssetByteInfoer::info(const std::filesystem::path& fp, const AssetInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        return info(bytes, api);
    }

    ///////////////////////////////////

    AssetByteLoader::AssetByteLoader(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        AssetFileLoader(meta, exts, sl, type)
    {
    }
    
    AssetByteLoader::~AssetByteLoader()
    {
    }

    Asset* AssetByteLoader::load(const std::filesystem::path& fp, const AssetLoadAPI& api) const
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        return load(bytes, api);
    }

    ///////////////////////////////////

    AssetByteSaver::AssetByteSaver(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        AssetFileSaver(meta, exts, sl, type)
    {
    }
    
    AssetByteSaver::~AssetByteSaver()
    {
    }

    std::error_code  AssetByteSaver::save(const Asset&asset, const std::filesystem::path&fp, const AssetSaveAPI&api) const
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
