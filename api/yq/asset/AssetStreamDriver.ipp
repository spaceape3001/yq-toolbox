////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssetStreamDriver.hpp"
//#include "StreamDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/file/FileUtils.hpp>
#include <fstream>

namespace yq {
    ///////////////////////////////////

    AssetStreamInfoer::AssetStreamInfoer(const AssetMeta& meta, const string_vector_t& exts, const std::source_location& sl, bool binary, Type type) :
        AssetFileInfoer(meta, exts, sl, type), m_binary(binary)
    {
    }

    AssetStreamInfoer::~AssetStreamInfoer()
    {
    }
    
    AssetInfo* AssetStreamInfoer::info(const std::filesystem::path& fp, const AssetInfoAPI&api) const 
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

    AssetStreamLoader::AssetStreamLoader(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, bool binary, Type type) : 
        AssetFileLoader(meta, exts, sl, type), m_binary(binary)
    {
    }
    
    AssetStreamLoader::~AssetStreamLoader()
    {
    }

    Asset* AssetStreamLoader::load(const std::filesystem::path& fp, const AssetLoadAPI& api) const
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

    AssetStreamSaver::AssetStreamSaver(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, bool binary, Type type) : 
        AssetFileSaver(meta, exts, sl, type), m_binary(binary)
    {
    }
    
    AssetStreamSaver::~AssetStreamSaver()
    {
    }

    std::error_code  AssetStreamSaver::save(const Asset&asset, const std::filesystem::path&fp, const AssetSaveAPI&api) const
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
