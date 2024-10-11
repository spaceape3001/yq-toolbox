////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    class Asset;
    class AssetCache;
    class AssetInfo;
    class AssetFactory;
    
    template <typename> class Ref;
    template <typename> class TypedAssetFactory;
    
    struct AssetLoadOptions;
    struct AssetSaveOptions;
    
    using AssetPtr      = Ref<Asset>;
    using AssetCPtr     = Ref<const Asset>;
}
