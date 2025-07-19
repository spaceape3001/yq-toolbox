////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ResourceByteDriver.hpp"
//#include "ByteDriver.hxx"
#include "ResourceLogging.hpp"
#include "ResourceDriverAPI.hpp"

#include <yq/container/ByteArray.hpp>
#include <yq/file/FileUtils.hpp>

namespace yq {
    ///////////////////////////////////

    ResourceByteInfoer::ResourceByteInfoer(const ResourceMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceFileInfoer(meta, exts, sl, type)
    {
    }

    ResourceByteInfoer::~ResourceByteInfoer()
    {
    }
    
    ResourceInfo* ResourceByteInfoer::info(const std::filesystem::path& fp, const ResourceInfoAPI&api) const 
    {
        if(!file_exists(fp)){
            resourceWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        return info(bytes, api);
    }

    ///////////////////////////////////

    ResourceByteLoader::ResourceByteLoader(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceFileLoader(meta, exts, sl, type)
    {
    }
    
    ResourceByteLoader::~ResourceByteLoader()
    {
    }

    Resource* ResourceByteLoader::load(const std::filesystem::path& fp, const ResourceLoadAPI& api) const
    {
        if(!file_exists(fp)){
            resourceWarning << "URL's file from " << api.spec() << " does not exist!";
            return nullptr;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        return load(bytes, api);
    }

    ///////////////////////////////////

    ResourceByteSaver::ResourceByteSaver(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceFileSaver(meta, exts, sl, type)
    {
    }
    
    ResourceByteSaver::~ResourceByteSaver()
    {
    }

    std::error_code  ResourceByteSaver::save(const Resource&resource, const std::filesystem::path&fp, const ResourceSaveAPI&api) const
    {
        ByteArray       bytes;
        std::error_code ec  = save(resource, bytes, api);
        if(ec != std::error_code())
            return ec;
        
        if(!file_write(fp, bytes))
            return errors::failed_to_write_file();
        return std::error_code();
    }

    ///////////////////////////////////
}
