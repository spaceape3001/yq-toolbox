////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ResourceStreamDriver.hpp"
//#include "StreamDriver.hxx"
#include "ResourceLogging.hpp"
#include "ResourceDriverAPI.hpp"

#include <yq/file/FileUtils.hpp>
#include <fstream>

namespace yq {
    ///////////////////////////////////

    ResourceStreamInfoer::ResourceStreamInfoer(const ResourceMeta& meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) :
        ResourceFileInfoer(meta, spec, sl, type), m_binary(spec.binary)
    {
    }

    ResourceStreamInfoer::~ResourceStreamInfoer()
    {
    }
    
    ResourceInfoPtr ResourceStreamInfoer::info(const std::filesystem::path& fp, const ResourceInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            resourceWarning << "URL's file from " << api.spec() << " does not exist!";
            return {};
        }
        
        std::ios_base::openmode     mode    = std::ios_base::in;
        if(m_binary)
            mode |= std::ios_base::binary;
        
        std::ifstream   fin(fp, mode);
        if(!fin){
            resourceWarning << "Unable to open " << fp << " for reading.";
            return {};
        }
        
        return info(fin, api);
    }

    ///////////////////////////////////

    ResourceStreamLoader::ResourceStreamLoader(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceFileLoader(meta, spec, sl, type), m_binary(spec.binary)
    {
    }
    
    ResourceStreamLoader::~ResourceStreamLoader()
    {
    }

    ResourcePtr ResourceStreamLoader::load(const std::filesystem::path& fp, const ResourceLoadAPI& api) const
    {
        if(!file_exists(fp)){
            resourceWarning << "URL's file from " << api.spec() << " does not exist!";
            return {};
        }
        
        std::ios_base::openmode     mode    = std::ios_base::in;
        if(m_binary)
            mode |= std::ios_base::binary;
        
        std::ifstream   fin(fp, mode);
        if(!fin){
            resourceWarning << "Unable to open " << fp << " for reading.";
            return {};
        }

        return load(fin, api);
    }

    ///////////////////////////////////

    ResourceStreamSaver::ResourceStreamSaver(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceFileSaver(meta, spec, sl, type), m_binary(spec.binary)
    {
    }
    
    ResourceStreamSaver::~ResourceStreamSaver()
    {
    }

    std::error_code  ResourceStreamSaver::save(const Resource&resource, const std::filesystem::path&fp, const ResourceSaveAPI&api) const
    {
        std::ios_base::openmode     mode    = std::ios_base::out | std::ios_base::trunc ;
        if(m_binary)
            mode |= std::ios_base::binary;
        std::ofstream   fout(fp, mode);
        if(!fout)
            return errors::cant_open_write();
        std::error_code ec = save(resource, fout, api);
        if(ec != std::error_code())
            return ec;
        fout.close();
        if(!fout)
            return errors::failed_to_write_file();
        return std::error_code();
    }

    ///////////////////////////////////
}
