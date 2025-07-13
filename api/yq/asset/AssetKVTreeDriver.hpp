////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetByteDriver.hpp>

namespace yq {
    class AssetKVTreeInfoer : public AssetByteInfoer {
    public:
    
        using AssetByteInfoer::info;
        virtual AssetInfo* info(const ByteArray&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const KVTree&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetKVTreeInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~AssetKVTreeInfoer();
        
    private:
        unsigned int m_options;
    };
    
    class AssetKVTreeLoader : public AssetByteLoader {
    public:

        using AssetByteLoader::load;
        virtual Asset* load(const ByteArray&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const KVTree&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetKVTreeLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool, Type type=Type::kvdoc);
        virtual ~AssetKVTreeLoader();
    private:
        unsigned int m_options;
    };

    class AssetKVTreeSaver : public AssetByteSaver {
    public:

        using AssetByteSaver::save;
        virtual std::error_code  save(const Asset&, ByteArray&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, KVTree&, const AssetSaveAPI&) const = 0;

    protected:
        AssetKVTreeSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::kvdoc);
        virtual ~AssetKVTreeSaver();
    };
}
