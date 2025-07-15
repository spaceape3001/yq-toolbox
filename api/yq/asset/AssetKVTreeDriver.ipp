////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssetKVTreeDriver.hpp"
//#include "KVTreeDriver.hxx"
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

    AssetKVTreeInfoer::AssetKVTreeInfoer(const AssetMeta& meta, const string_vector_t& exts, const std::source_location& sl, bool recurse, Type type) :
        AssetByteInfoer(meta, exts, sl, type), m_options(0)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }

    AssetKVTreeInfoer::~AssetKVTreeInfoer()
    {
    }
    
    AssetInfo* AssetKVTreeInfoer::info(const ByteArray& file, const AssetInfoAPI&api) const 
    {
        KVTree      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return nullptr;
        return info(doc, api);
    }

    ///////////////////////////////////

    AssetKVTreeLoader::AssetKVTreeLoader(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, bool recurse, Type type) : 
        AssetByteLoader(meta, exts, sl, type), m_options(0)
    {
        if(recurse)
            m_options |= KVTree::RECURSIVE;
    }
    
    AssetKVTreeLoader::~AssetKVTreeLoader()
    {
    }

    Asset* AssetKVTreeLoader::load(const ByteArray& file, const AssetLoadAPI& api) const
    {
        KVTree      doc;
            
            // which will be boolean until key-values return std::error_code
        auto ret    = doc.parse(file.as_view(), api.spec(), m_options);
        if(ret.ec != std::error_code()) [[unlikely]]
            return nullptr;
        return load(doc, api);
    }

    ///////////////////////////////////

    AssetKVTreeSaver::AssetKVTreeSaver(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        AssetByteSaver(meta, exts, sl, type)
    {
    }
    
    AssetKVTreeSaver::~AssetKVTreeSaver()
    {
    }

    std::error_code  AssetKVTreeSaver::save(const Asset&asset, ByteArray& data, const AssetSaveAPI&api) const
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
