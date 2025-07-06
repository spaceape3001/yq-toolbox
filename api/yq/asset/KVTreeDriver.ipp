////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "KVTreeDriver.hpp"
#include "KVTreeDriver.hxx"
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

    Asset::KVTreeInfoer::KVTreeInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, bool recurse, Type type) :
        ByteInfoer(meta, exts, sl, type), m_options(0)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }

    Asset::KVTreeInfoer::~KVTreeInfoer()
    {
    }
    
    AssetInfo* Asset::KVTreeInfoer::info(const ByteArray& file, const AssetInfoAPI&api) const 
    {
        KVTree      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return nullptr;
        return info(doc, api);
    }

    ///////////////////////////////////

    Asset::KVTreeLoader::KVTreeLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, bool recurse, Type type) : 
        ByteLoader(meta, exts, sl, type), m_options(0)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }
    
    Asset::KVTreeLoader::~KVTreeLoader()
    {
    }

    Asset* Asset::KVTreeLoader::load(const ByteArray& file, const AssetLoadAPI& api) const
    {
        KVTree      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return nullptr;
        return load(doc, api);
    }

    ///////////////////////////////////

    Asset::KVTreeSaver::KVTreeSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        ByteSaver(meta, exts, sl, type)
    {
    }
    
    Asset::KVTreeSaver::~KVTreeSaver()
    {
    }

    std::error_code  Asset::KVTreeSaver::save(const Asset&asset, ByteArray& data, const AssetSaveAPI&api) const
    {
        KVTree     doc;
        std::error_code ec  = save(asset, doc, api);
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
