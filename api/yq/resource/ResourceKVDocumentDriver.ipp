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

    ResourceKVDocumentInfoer::ResourceKVDocumentInfoer(const ResourceMeta& meta, const string_vector_t& exts, const std::source_location& sl, bool recurse, Type type) :
        ResourceByteInfoer(meta, exts, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }

    ResourceKVDocumentInfoer::~ResourceKVDocumentInfoer()
    {
    }
    
    ResourceInfo* ResourceKVDocumentInfoer::info(const ByteArray& file, const ResourceInfoAPI&api) const 
    {
        KVDocument      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return nullptr;
        doc.body    = std::move(ret.body);
        return info(doc, api);
    }

    ///////////////////////////////////

    ResourceKVDocumentLoader::ResourceKVDocumentLoader(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, bool recurse, Type type) : 
        ResourceByteLoader(meta, exts, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }
    
    ResourceKVDocumentLoader::~ResourceKVDocumentLoader()
    {
    }

    Resource* ResourceKVDocumentLoader::load(const ByteArray& file, const ResourceLoadAPI& api) const
    {
        KVDocument      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return nullptr;
        doc.body    = std::move(ret.body);
        return load(doc, api);
    }

    ///////////////////////////////////

    ResourceKVDocumentSaver::ResourceKVDocumentSaver(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceByteSaver(meta, exts, sl, type)
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
