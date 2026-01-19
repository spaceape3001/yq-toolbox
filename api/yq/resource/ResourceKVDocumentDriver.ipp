////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ResourceKVDocumentDriver.hpp"
//#include "KVDocumentDriver.hxx"
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

    ResourceKVDocumentInfoer::ResourceKVDocumentInfoer(const ResourceMeta& meta, const ResourceIOSpec& spec, const std::source_location& sl, bool recurse, Type type) :
        ResourceByteInfoer(meta, spec, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }

    ResourceKVDocumentInfoer::~ResourceKVDocumentInfoer()
    {
    }
    
    ResourceInfoPtr ResourceKVDocumentInfoer::info(const ByteArray& file, const ResourceInfoAPI&api) const 
    {
        KVDocument      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return {};
        doc.body    = std::move(ret.body);
        return info(doc, api);
    }

    ///////////////////////////////////

    ResourceKVDocumentLoader::ResourceKVDocumentLoader(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, bool recurse, Type type) : 
        ResourceByteLoader(meta, spec, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }
    
    ResourceKVDocumentLoader::~ResourceKVDocumentLoader()
    {
    }

    ResourcePtr ResourceKVDocumentLoader::load(const ByteArray& file, const ResourceLoadAPI& api) const
    {
        KVDocument      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return {};
        doc.body    = std::move(ret.body);
        return load(doc, api);
    }

    ///////////////////////////////////

    ResourceKVDocumentSaver::ResourceKVDocumentSaver(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceByteSaver(meta, spec, sl, type)
    {
    }
    
    ResourceKVDocumentSaver::~ResourceKVDocumentSaver()
    {
    }

    std::error_code  ResourceKVDocumentSaver::save(const Resource&resource, ByteArray& data, const ResourceSaveAPI&api) const
    {
        KVDocument     doc;
        std::error_code ec  = save(resource, doc, api);
        if(ec != std::error_code())
            return ec;
            
        stream::Bytes   bytes(data);
        doc.write(bytes);
        if(!doc.body.empty()){
            bytes << '\n' << doc.body;
        }
        bytes.flush();
        bytes.close();
        return std::error_code();
    }

    ///////////////////////////////////
}
