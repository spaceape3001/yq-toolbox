////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetFileDriver.hpp>

namespace yq {
    class AssetByteInfoer : public AssetFileInfoer {
    public:
    
        using AssetFileInfoer::info;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const ByteArray&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetByteInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::byte);
        virtual ~AssetByteInfoer();
    };
    
    class AssetByteLoader : public AssetFileLoader {
    public:

        using AssetFileLoader::load;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const ByteArray&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetByteLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::byte);
        virtual ~AssetByteLoader();
    };

    class AssetByteSaver : public AssetFileSaver {
    public:

        using AssetFileSaver::save;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, ByteArray&, const AssetSaveAPI&) const = 0;

    protected:
        AssetByteSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::byte);
        virtual ~AssetByteSaver();
    };
}
