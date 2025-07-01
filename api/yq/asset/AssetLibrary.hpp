////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/text/IgCase.hpp>

namespace yq {
    class AssetLibraryInfo : public AssetMeta {
    public:
    
        template <typename C> class Writer;

        //! Constructor of asset library info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        AssetLibraryInfo(std::string_view zName, AssetMeta& base, const std::source_location& sl=std::source_location::current());
        
        //! Base type of the library asset
        const AssetMeta*    asset() const { return m_asset; }
    
    private:
        const AssetMeta*    m_asset = nullptr;
    };

    class AssetLibrary : public Asset {
        YQ_OBJECT_INFO(AssetLibraryInfo)
        YQ_OBJECT_DECLARE(AssetLibrary, Asset)
    public:
    
    protected:
        AssetLibrary();
        ~AssetLibrary();
        
        std::multimap<std::string,AssetCPtr,IgCase>    m_assets;
    
    };
    
    template <typename A>
    class TypedAssetLibrary : public AssetLibrary {
    };
}
