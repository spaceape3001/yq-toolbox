////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssetKVDocumentDriver.hpp"
//#include "KVDocumentDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/container/ByteArray.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/keyv/KeyValue.hpp>
#include <yq/stream/Bytes.hpp>

/*
    PENDING -- TO FINISH (LATER)
*/

namespace yq {
    ///////////////////////////////////

    AssetKVDocumentInfoer::AssetKVDocumentInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, bool recurse, Type type) :
        AssetByteInfoer(meta, exts, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }

    AssetKVDocumentInfoer::~AssetKVDocumentInfoer()
    {
    }
    
    AssetInfo* AssetKVDocumentInfoer::info(const ByteArray& file, const AssetInfoAPI&api) const 
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

    AssetKVDocumentLoader::AssetKVDocumentLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, bool recurse, Type type) : 
        AssetByteLoader(meta, exts, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }
    
    AssetKVDocumentLoader::~AssetKVDocumentLoader()
    {
    }

    Asset* AssetKVDocumentLoader::load(const ByteArray& file, const AssetLoadAPI& api) const
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

    AssetKVDocumentSaver::AssetKVDocumentSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        AssetByteSaver(meta, exts, sl, type)
    {
    }
    
    AssetKVDocumentSaver::~AssetKVDocumentSaver()
    {
    }

    std::error_code  AssetKVDocumentSaver::save(const Asset&asset, ByteArray& data, const AssetSaveAPI&api) const
    {
        KVDocument     doc;
        std::error_code ec  = save(asset, doc, api);
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
