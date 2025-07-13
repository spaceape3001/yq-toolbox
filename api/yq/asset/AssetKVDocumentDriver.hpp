////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetByteDriver.hpp>

namespace yq {
    class AssetKVDocumentInfoer : public AssetByteInfoer {
    public:
    
        using AssetByteInfoer::info;
        virtual AssetInfo* info(const ByteArray&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const KVDocument&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetKVDocumentInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~AssetKVDocumentInfoer();
        
    private:
        unsigned int m_options;
    };
    
    class AssetKVDocumentLoader : public AssetByteLoader {
    public:

        using AssetByteLoader::load;
        virtual Asset* load(const ByteArray&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const KVDocument&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetKVDocumentLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~AssetKVDocumentLoader();
    private:
        unsigned int m_options;
    };

    class AssetKVDocumentSaver : public AssetByteSaver {
    public:

        using AssetByteSaver::save;
        virtual std::error_code  save(const Asset&, ByteArray&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, KVDocument&, const AssetSaveAPI&) const = 0;

    protected:
        AssetKVDocumentSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::kvdoc);
        virtual ~AssetKVDocumentSaver();
    };
}
