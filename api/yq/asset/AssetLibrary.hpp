////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/text/IgCase.hpp>

namespace yq {
    class AssetLibraryMeta : public AssetMeta {
    public:
    
        template <typename C> class Writer;

        //! Constructor of asset library info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        AssetLibraryMeta(std::string_view zName, AssetMeta& base, const std::source_location& sl=std::source_location::current());
        
        //! Asset types this library can contain (empty implies all)
        const std::vector<const AssetMeta*>& assets() const { return m_assets; }
    
    private:
        std::vector<const AssetMeta*>   m_assets;
    };
    
    class AssetLibraryInfo : public AssetInfo {
        YQ_OBJECT_DECLARE(AssetLibraryInfo, AssetInfo)
    public:
        
    };

    class AssetLibrary : public Asset {
        YQ_ASSET_META(AssetLibraryMeta)
        YQ_ASSET_INFO(AssetLibraryInfo)
        YQ_ASSET_DECLARE(AssetLibrary, Asset)
    public:
    
        bool    contains(const std::string&) const;
    
        static void init_meta();
        
        AssetCPtr   asset(const std::string&) const;
    
        void        add(std::string_view, AssetPtr);
    
    protected:
        friend class Asset;
        
        AssetLibrary();
        virtual ~AssetLibrary();
        
        std::map<std::string,AssetCPtr,IgCase>    m_assets;
    };
}
