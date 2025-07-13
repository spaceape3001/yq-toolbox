////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetFileDriver.hpp>

namespace yq {
    class AssetStringInfoer : public AssetFileInfoer {
    public:
    
        using AssetFileInfoer::info;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const std::string&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetStringInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::string);
        virtual ~AssetStringInfoer();
    };
    
    class AssetStringLoader : public AssetFileLoader {
    public:

        using AssetFileLoader::load;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const std::string&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetStringLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::string);
        virtual ~AssetStringLoader();
    };

    class AssetStringSaver : public AssetFileSaver {
    public:

        using AssetFileSaver::save;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, std::string&, const AssetSaveAPI&) const = 0;

    protected:
        AssetStringSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::string);
        virtual ~AssetStringSaver();
    };
}
