////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "KVDocumentDriver.hpp"
#include "KVDocumentDriver.hxx"
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

    Asset::KVDocumentInfoer::KVDocumentInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, bool recurse, Type type) :
        ByteInfoer(meta, exts, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }

    Asset::KVDocumentInfoer::~KVDocumentInfoer()
    {
    }
    
    AssetInfo* Asset::KVDocumentInfoer::info(const ByteArray& file, const AssetInfoAPI&api) const 
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

    Asset::KVDocumentLoader::KVDocumentLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, bool recurse, Type type) : 
        ByteLoader(meta, exts, sl, type), m_options(KVTree::BODY)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }
    
    Asset::KVDocumentLoader::~KVDocumentLoader()
    {
    }

    Asset* Asset::KVDocumentLoader::load(const ByteArray& file, const AssetLoadAPI& api) const
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

    Asset::KVDocumentSaver::KVDocumentSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        ByteSaver(meta, exts, sl, type)
    {
    }
    
    Asset::KVDocumentSaver::~KVDocumentSaver()
    {
    }

    std::error_code  Asset::KVDocumentSaver::save(const Asset&asset, ByteArray& data, const AssetSaveAPI&api) const
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
