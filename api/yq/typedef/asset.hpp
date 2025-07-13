////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <concepts>

namespace yq {
    template <typename> class Ref;      // general forward declaration


    class Asset;                //< Asset itself
    class AssetBinder;          //< Allows for dynamic binding of asset
    class AssetMeta;            //< Asset class meta information
    class AssetLibrary;         //< Collection of assets, keyed by integers and/or strings
    class AssetLibraryMeta;     //< Asset Library class meta inforamtion
    
    struct AssetInfo;           //< Asset information (for the specific)
    struct AssetRepo;           //< Internal repository for asset information

    
    struct AssetInfoOptions;    //< Asset load options
    struct AssetLoadOptions;    //< Asset load options
    struct AssetSaveOptions;    //< Asset save options

    class AssetLoadAPI;
    class AssetInfoAPI;
    class AssetSaveAPI;
    
    using AssetPtr              = Ref<Asset>;                   //!< Asset pointer
    using AssetCPtr             = Ref<const Asset>;             //!< Asset const pointer
    using AssetLibraryPtr       = Ref<AssetLibrary>;            //!< AssetLibrary pointer
    using AssetLibraryCPtr      = Ref<const AssetLibrary>;      //!< AssetLibrary const pointer

    using AssetInfoPtr          = Ref<AssetInfo>;
    using AssetInfoCPtr         = Ref<const AssetInfo>;

    //! Concept for an asset
    template <class A>
    concept SomeAsset = std::derived_from<A,Asset>;

    //! Concept for an asset library
    template <class A>
    concept SomeAssetLibrary = std::derived_from<A,AssetLibrary>;
    
    //template <SomeAsset> class TypedAssetLibrary;
    //template <SomeAsset> class TypedAssetLibraryFixer;
    //template <typename> class TypedAssetFactory;

    template <class A> class AssetRef;
    
    class AssetDriver;
    class AssetLoader;
    class AssetInfoer;
    class AssetSaver;
}
