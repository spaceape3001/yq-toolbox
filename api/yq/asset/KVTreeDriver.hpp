////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/ByteDriver.hpp>

namespace yq {
    class Asset::KVTreeInfoer : public ByteInfoer {
    public:
    
        using ByteInfoer::info;
        virtual AssetInfo* info(const ByteArray&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const KVTree&, const AssetInfoAPI&) const = 0;
        
    protected:
        KVTreeInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~KVTreeInfoer();
        
    private:
        unsigned int m_options;
    };
    
    class Asset::KVTreeLoader : public ByteLoader {
    public:

        using ByteLoader::load;
        virtual Asset* load(const ByteArray&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const KVTree&, const AssetLoadAPI&) const = 0;
        
    protected:
        KVTreeLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~KVTreeLoader();
    private:
        unsigned int m_options;
    };

    class Asset::KVTreeSaver : public ByteSaver {
    public:

        using ByteSaver::save;
        virtual std::error_code  save(const Asset&, ByteArray&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, KVTree&, const AssetSaveAPI&) const = 0;

    protected:
        KVTreeSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::kvdoc);
        virtual ~KVTreeSaver();
    };
}
