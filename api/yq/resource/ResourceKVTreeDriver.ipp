////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ResourceKVTreeDriver.hpp"
//#include "KVTreeDriver.hxx"
#include "ResourceLogging.hpp"
#include "ResourceDriverAPI.hpp"

#include <yq/container/ByteArray.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/keyv/KeyValue.hpp>
#include <yq/stream/Bytes.hpp>

/*
    PENDING -- TO FINISH (LATER)
*/

namespace yq {
    ///////////////////////////////////

    ResourceKVTreeInfoer::ResourceKVTreeInfoer(const ResourceMeta& meta, const ResourceIOSpec& spec, const std::source_location& sl, bool recurse, Type type) :
        ResourceByteInfoer(meta, spec, sl, type), m_options(0)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }

    ResourceKVTreeInfoer::~ResourceKVTreeInfoer()
    {
    }
    
    ResourceInfoPtr ResourceKVTreeInfoer::info(const ByteArray& file, const ResourceInfoAPI&api) const 
    {
        KVTree      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return {};
        return info(doc, api);
    }

    ///////////////////////////////////

    ResourceKVTreeLoader::ResourceKVTreeLoader(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, bool recurse, Type type) : 
        ResourceByteLoader(meta, spec, sl, type), m_options(0)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }
    
    ResourceKVTreeLoader::~ResourceKVTreeLoader()
    {
    }

    ResourcePtr ResourceKVTreeLoader::load(const ByteArray& file, const ResourceLoadAPI& api) const
    {
        KVTree      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return {};
        return load(doc, api);
    }

    ///////////////////////////////////

    ResourceKVTreeSaver::ResourceKVTreeSaver(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceByteSaver(meta, spec, sl, type)
    {
    }
    
    ResourceKVTreeSaver::~ResourceKVTreeSaver()
    {
    }

    std::error_code  ResourceKVTreeSaver::save(const Resource&resource, ByteArray& data, const ResourceSaveAPI&api) const
    {
        KVTree     doc;
        std::error_code ec  = save(resource, doc, api);
        if(ec != std::error_code())
            return ec;
            
        stream::Bytes   bytes(data);
        doc.write(bytes);
        bytes.flush();
        bytes.close();
        return std::error_code();
    }

    ///////////////////////////////////
}
