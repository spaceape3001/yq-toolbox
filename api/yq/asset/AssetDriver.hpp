////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/core/ErrorDB.hpp>

namespace yq {

    class Asset::Driver {
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
        Driver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~Driver();
        
    private:
        const AssetMeta&        m_asset;
        string_set_t            m_extensions;
        std::source_location    m_location;
        Type                    m_type;
    };

    class Asset::Infoer : public Driver {
    public:

        virtual AssetInfo* info(const UrlView&, const AssetInfoAPI&) const = 0;

    protected:
        friend class Asset;
        
        Infoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~Infoer();
    };
    
    class Asset::Loader : public Driver {
    public:

        virtual Asset* load(const UrlView&, const AssetLoadAPI&) const = 0;

    protected:
        friend class Asset;

        Loader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~Loader();
    };

    class Asset::Saver : public Driver {
    public:
        virtual std::error_code  save(const Asset&, const UrlView&, const AssetSaveAPI&) const = 0;
        
    protected:
        friend class Asset;

        Saver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, Type);
        virtual ~Saver();
    };
    
    namespace errors {
        using asset_saving_failed   = error_db::entry<"Unable to save asset">;
    }
}
