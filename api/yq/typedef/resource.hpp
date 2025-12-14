////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <concepts>

namespace yq {
    template <typename> class Ref;      // general forward declaration


    class Resource;                //< Resource itself
    class ResourceBinder;          //< Allows for dynamic binding of resource
    class ResourceMeta;            //< Resource class meta information
    class ResourceLibrary;         //< Collection of resources, keyed by integers and/or strings
    class ResourceLibraryMeta;     //< Resource Library class meta inforamtion
    
    class ResourceInfo;            //< Resource information (for the specific)
    struct ResourceRepo;           //< Internal repository for resource information

    class ResourceInfoMeta;

    
    struct ResourceInfoOptions;    //< Resource load options
    struct ResourceLoadOptions;    //< Resource load options
    struct ResourceSaveOptions;    //< Resource save options

    class ResourceLoadAPI;
    class ResourceInfoAPI;
    class ResourceSaveAPI;
    
    using ResourcePtr              = Ref<Resource>;                   //!< Resource pointer
    using ResourceCPtr             = Ref<const Resource>;             //!< Resource const pointer
    using ResourceLibraryPtr       = Ref<ResourceLibrary>;            //!< ResourceLibrary pointer
    using ResourceLibraryCPtr      = Ref<const ResourceLibrary>;      //!< ResourceLibrary const pointer

    using ResourceInfoPtr          = Ref<ResourceInfo>;
    using ResourceInfoCPtr         = Ref<const ResourceInfo>;

    //! Concept for an resource
    template <class A>
    concept SomeResource = std::derived_from<A,Resource>;

    //! Concept for an resource library
    template <class A>
    concept SomeResourceLibrary = std::derived_from<A,ResourceLibrary>;
    
    //template <SomeResource> class TypedResourceLibrary;
    //template <SomeResource> class TypedResourceLibraryFixer;
    //template <typename> class TypedResourceFactory;

    template <class A> class ResourceRef;
    
    class ResourceDriver;
    class ResourceLoader;
    class ResourceInfoer;
    class ResourceConverter;
    class ResourceSaver;
}
