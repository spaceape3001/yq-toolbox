////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/StringDriver.hpp>

namespace yq {
    class Asset::JsonInfoer : public StringInfoer {
    public:
    
        using StringInfoer::info;
        virtual AssetInfo* info(const std::string&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const json&, const AssetInfoAPI&) const = 0;
        
    protected:
        JsonInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::json);
        virtual ~JsonInfoer();
    };
    
    class Asset::JsonLoader : public StringLoader {
    public:

        using StringLoader::load;
        virtual Asset* load(const std::string&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const json&, const AssetLoadAPI&) const = 0;
        
    protected:
        JsonLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::json);
        virtual ~JsonLoader();
    };

    class Asset::JsonSaver : public StringSaver {
    public:

        using StringSaver::save;
        virtual std::error_code  save(const Asset&, std::string&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, json&, const AssetSaveAPI&) const = 0;

    protected:
        JsonSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::json);
        virtual ~JsonSaver();
    };
}
