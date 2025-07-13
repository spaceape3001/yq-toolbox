////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/core/ErrorDB.hpp>

namespace yq {

    class AssetDriver {
        friend class Asset;
    public:
    
        enum class Type : uint8_t {
            none    = 0,
            url,
            file,
            byte,
            stream,
            string,
            xml,
            json,
            kvdoc,
            kvtree
        };
        
        Type                type() const { return m_type; }
        const AssetMeta&    asset() const { return m_asset; }

        constexpr const string_set_t& extensions() const { return m_extensions; }
        constexpr const std::source_location& location() const { return m_location; }
        
    protected:
        AssetDriver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~AssetDriver();
        
    private:
        const AssetMeta&        m_asset;
        string_set_t            m_extensions;
        std::source_location    m_location;
        Type                    m_type;
    };

    class AssetInfoer : public AssetDriver {
    public:

        virtual AssetInfo* info(const UrlView&, const AssetInfoAPI&) const = 0;

    protected:
        friend class Asset;
        
        AssetInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~AssetInfoer();
    };
    
    class AssetLoader : public AssetDriver {
    public:

        virtual Asset* load(const UrlView&, const AssetLoadAPI&) const = 0;

    protected:
        friend class Asset;

        AssetLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~AssetLoader();
    };

    class AssetSaver : public AssetDriver {
    public:
        virtual std::error_code  save(const Asset&, const UrlView&, const AssetSaveAPI&) const = 0;
        
    protected:
        friend class Asset;

        AssetSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~AssetSaver();
    };
    
    namespace errors {
        using asset_saving_failed   = error_db::entry<"Unable to save asset">;
    }
}
