////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/ByteDriver.hpp>

namespace yq {
    class Asset::KVDocumentInfoer : public ByteInfoer {
    public:
    
        using ByteInfoer::info;
        virtual AssetInfo* info(const ByteArray&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const KVDocument&, const AssetInfoAPI&) const = 0;
        
    protected:
        KVDocumentInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~KVDocumentInfoer();
        
    private:
        unsigned int m_options;
    };
    
    class Asset::KVDocumentLoader : public ByteLoader {
    public:

        using ByteLoader::load;
        virtual Asset* load(const ByteArray&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const KVDocument&, const AssetLoadAPI&) const = 0;
        
    protected:
        KVDocumentLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~KVDocumentLoader();
    private:
        unsigned int m_options;
    };

    class Asset::KVDocumentSaver : public ByteSaver {
    public:

        using ByteSaver::save;
        virtual std::error_code  save(const Asset&, ByteArray&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, KVDocument&, const AssetSaveAPI&) const = 0;

    protected:
        KVDocumentSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::kvdoc);
        virtual ~KVDocumentSaver();
    };
}
