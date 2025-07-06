////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StreamDriver.hpp"
#include "StreamDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/file/FileUtils.hpp>
#include <fstream>

namespace yq {
    ///////////////////////////////////

    Asset::StreamInfoer::StreamInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, bool binary, Type type) :
        FileInfoer(meta, exts, sl, type), m_binary(binary)
    {
    }

    Asset::StreamInfoer::~StreamInfoer()
    {
    }
    
    AssetInfo* Asset::StreamInfoer::info(const std::filesystem::path& fp, const AssetInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::ios_base::openmode     mode    = std::ios_base::in;
        if(m_binary)
            mode |= std::ios_base::binary;
        
        std::ifstream   fin(fp, mode);
        if(!fin){
            assetWarning << "Unable to open " << fp << " for reading.";
            return nullptr;
        }
        
        return info(fin, api);
    }

    ///////////////////////////////////

    Asset::StreamLoader::StreamLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, bool binary, Type type) : 
        FileLoader(meta, exts, sl, type), m_binary(binary)
    {
    }
    
    Asset::StreamLoader::~StreamLoader()
    {
    }

    Asset* Asset::StreamLoader::load(const std::filesystem::path& fp, const AssetLoadAPI& api) const
    {
        if(!file_exists(fp)){
            assetWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        std::ios_base::openmode     mode    = std::ios_base::in;
        if(m_binary)
            mode |= std::ios_base::binary;
        
        std::ifstream   fin(fp, mode);
        if(!fin){
            assetWarning << "Unable to open " << fp << " for reading.";
            return nullptr;
        }

        return load(fin, api);
    }

    ///////////////////////////////////

    Asset::StreamSaver::StreamSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, bool binary, Type type) : 
        FileSaver(meta, exts, sl, type), m_binary(binary)
    {
    }
    
    Asset::StreamSaver::~StreamSaver()
    {
    }

    std::error_code  Asset::StreamSaver::save(const Asset&asset, const std::filesystem::path&fp, const AssetSaveAPI&api) const
    {
        std::ios_base::openmode     mode    = std::ios_base::out | std::ios_base::trunc ;
        if(m_binary)
            mode |= std::ios_base::binary;
        std::ofstream   fout(fp, mode);
        if(!fout)
            return errors::cant_open_write();
        std::error_code ec = save(asset, fout, api);
        if(ec != std::error_code())
            return ec;
        fout.close();
        if(!fout)
            return errors::failed_to_write_file();
        return std::error_code();
    }

    ///////////////////////////////////
}
