////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetDriver.hpp>

namespace yq {
    class AssetFileInfoer : public AssetInfoer {
    public:
    
        virtual AssetInfo* info(const UrlView&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetFileInfoer(const AssetMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::file);
        virtual ~AssetFileInfoer();
    };
    
    class AssetFileLoader : public AssetLoader {
    public:
    
        virtual Asset* load(const UrlView&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetFileLoader(const AssetMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::file);
        virtual ~AssetFileLoader();
    };

    class AssetFileSaver : public AssetSaver {
    public:

        virtual std::error_code  save(const Asset&, const UrlView&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const = 0;

    protected:
        AssetFileSaver(const AssetMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::file);
        virtual ~AssetFileSaver();
    };
}
