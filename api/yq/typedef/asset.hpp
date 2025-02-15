////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <concepts>

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

    template <class E>
    concept SomeAsset = std::derived_from<E,Asset>;
}
