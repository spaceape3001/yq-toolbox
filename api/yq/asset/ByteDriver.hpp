////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/FileDriver.hpp>

namespace yq {
    class Asset::ByteInfoer : public FileInfoer {
    public:
    
        using FileInfoer::info;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const ByteArray&, const AssetInfoAPI&) const = 0;
        
    protected:
        ByteInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::byte);
        virtual ~ByteInfoer();
    };
    
    class Asset::ByteLoader : public FileLoader {
    public:

        using FileLoader::load;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const ByteArray&, const AssetLoadAPI&) const = 0;
        
    protected:
        ByteLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::byte);
        virtual ~ByteLoader();
    };

    class Asset::ByteSaver : public FileSaver {
    public:

        using FileSaver::save;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, ByteArray&, const AssetSaveAPI&) const = 0;

    protected:
        ByteSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::byte);
        virtual ~ByteSaver();
    };
}
