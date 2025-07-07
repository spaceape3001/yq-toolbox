////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/asset.hpp>
#include <yq/net/Url.hpp>
#include <yq/asset/AssetIO.hpp>

namespace yq {

    class AssetInfoAPI {
    public:
    
        std::string_view            spec() const { return m_spec; }
        const Url&                  url() const { return m_url; }

        bool                        contains(uint32_t) const;
        bool                        contains(const std::string&) const;
    
        const Any&                  operator[](uint32_t) const;
        const Any&                  operator[](const std::string&) const;
    
    private:
        friend class Asset;

        AssetInfoAPI(const AssetInfoOptions&);
        AssetInfoAPI(AssetInfoOptions&&) = delete;
        ~AssetInfoAPI();

        const AssetInfoOptions&     m_options;
        std::string_view            m_spec;
        Url                         m_url;
    };

    class AssetLoadAPI {
    public:
    
        std::string_view            spec() const { return m_spec; }
        const Url&                  url() const { return m_url; }
    
        bool                        contains(uint32_t) const;
        bool                        contains(const std::string&) const;
    
        const Any&                  operator[](uint32_t) const;
        const Any&                  operator[](const std::string&) const;
        

    private:
        friend class Asset;
        
        AssetLoadAPI(const AssetLoadOptions&);
        AssetLoadAPI(AssetLoadOptions&&) = delete;
        ~AssetLoadAPI();
        
        const AssetLoadOptions&     m_options;
        std::string_view            m_spec;
        Url                         m_url;
    };
    
    
    class AssetSaveAPI {
    public:
    
        const Url&                  url() const { return m_url; }
        
        bool                        contains(uint32_t) const;
        bool                        contains(const std::string&) const;
    
        const Any&                  operator[](uint32_t) const;
        const Any&                  operator[](const std::string&) const;

        FileCollisionStrategy       collision() const { return m_options.collision; }
        bool                        set_name() const { return m_options.set_name; }
    
    private:
        friend class Asset;
        
        AssetSaveAPI(const AssetSaveOptions&);
        AssetSaveAPI(AssetSaveOptions&&) = delete;
        ~AssetSaveAPI();

        const AssetSaveOptions&     m_options;
        Url                         m_url;
    };

}
