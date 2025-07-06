////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/StringDriver.hpp>

namespace yq {
    class Asset::XmlInfoer : public StringInfoer {
    public:
    
        using StringInfoer::info;
        virtual AssetInfo* info(const std::string&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const XmlDocument&, const AssetInfoAPI&) const = 0;
        
    protected:
        XmlInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::xml);
        virtual ~XmlInfoer();
    };
    
    class Asset::XmlLoader : public StringLoader {
    public:

        using StringLoader::load;
        virtual Asset* load(const std::string&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const XmlDocument&, const AssetLoadAPI&) const = 0;
        
    protected:
        XmlLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::xml);
        virtual ~XmlLoader();
    };

    class Asset::XmlSaver : public StringSaver {
    public:

        using StringSaver::save;
        virtual std::error_code  save(const Asset&, std::string&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, XmlDocument&, const AssetSaveAPI&) const = 0;

    protected:
        XmlSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::xml);
        virtual ~XmlSaver();
    };
}
