////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetStringDriver.hpp>

namespace yq {
    class AssetXmlInfoer : public AssetStringInfoer {
    public:
    
        using AssetStringInfoer::info;
        virtual AssetInfo* info(const std::string&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const XmlDocument&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetXmlInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::xml);
        virtual ~AssetXmlInfoer();
    };
    
    class AssetXmlLoader : public AssetStringLoader {
    public:

        using AssetStringLoader::load;
        virtual Asset* load(const std::string&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const XmlDocument&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetXmlLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::xml);
        virtual ~AssetXmlLoader();
    };

    class AssetXmlSaver : public AssetStringSaver {
    public:

        using AssetStringSaver::save;
        virtual std::error_code  save(const Asset&, std::string&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, XmlDocument&, const AssetSaveAPI&) const = 0;

    protected:
        AssetXmlSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type type=Type::xml);
        virtual ~AssetXmlSaver();
    };
}
