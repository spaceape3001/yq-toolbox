////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetDriver.hpp>

namespace yq {
    class Asset::FileInfoer : public Infoer {
    public:
    
        virtual AssetInfo* info(const UrlView&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const = 0;
        
    protected:
        FileInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::file);
        virtual ~FileInfoer();
    };
    
    class Asset::FileLoader : public Loader {
    public:
    
        virtual Asset* load(const UrlView&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const = 0;
        
    protected:
        FileLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::file);
        virtual ~FileLoader();
    };

    class Asset::FileSaver : public Saver {
    public:

        virtual std::error_code  save(const Asset&, const UrlView&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const = 0;

    protected:
        FileSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::file);
        virtual ~FileSaver();
    };
}
