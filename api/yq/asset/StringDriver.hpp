////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/FileDriver.hpp>

namespace yq {
    class Asset::StringInfoer : public FileInfoer {
    public:
    
        using FileInfoer::info;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const std::string&, const AssetInfoAPI&) const = 0;
        
    protected:
        StringInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::string);
        virtual ~StringInfoer();
    };
    
    class Asset::StringLoader : public FileLoader {
    public:

        using FileLoader::load;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const std::string&, const AssetLoadAPI&) const = 0;
        
    protected:
        StringLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::string);
        virtual ~StringLoader();
    };

    class Asset::StringSaver : public FileSaver {
    public:

        using FileSaver::save;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, std::string&, const AssetSaveAPI&) const = 0;

    protected:
        StringSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::string);
        virtual ~StringSaver();
    };
}
