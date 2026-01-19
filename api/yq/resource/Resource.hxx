////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/resource/ResourceByteDriver.hxx>
#include <yq/resource/ResourceConverter.hxx>
#include <yq/resource/ResourceFileDriver.hxx>
#include <yq/resource/ResourceJsonDriver.hxx>
#include <yq/resource/ResourceKVDocumentDriver.hxx>
#include <yq/resource/ResourceKVTreeDriver.hxx>
#include <yq/resource/ResourceStreamDriver.hxx>
#include <yq/resource/ResourceStringDriver.hxx>
#include <yq/resource/ResourceUrlDriver.hxx>
#include <yq/resource/ResourceXmlDriver.hxx>
#include <yq/trait/always_false.hpp>
#include <type_traits>

namespace yq {
    template <typename A>
    template <SomeResource B, typename Pred>
    void ResourceIO<A>::add_converter_to(Pred&&fn, const std::source_location& sl)
    {
        Resource::add_converter( new TypedResourceConverter<A,B,Pred>(std::move(fn), sl));
    }
    
    template <typename A>
    template <SomeResource B, typename Pred>
    void ResourceIO<A>::add_converter_from(Pred&&fn, const std::source_location& sl)
    {
        Resource::add_converter( new TypedResourceConverter<B,A,Pred>(std::move(fn), sl));
    }

    template <typename A>
        template <typename Pred>
    void ResourceIO<A>::add_infoer(const ResourceIOSpec&sp, Pred&&fn, const std::source_location& sl)
    {
        using MyInfoPtr = Ref<typename A::MyInfo>;
    
        if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const ByteArray&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceByteInfoer<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const ByteArray&>){
            Resource::add_infoer( new TypedResourceByteInfoerNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const json&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceJsonInfoer<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const json&>){
            Resource::add_infoer( new TypedResourceJsonInfoerNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const KVDocument&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceKVDocumentInfoer<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const KVDocument&>){
            Resource::add_infoer( new TypedResourceKVDocumentInfoerNoAPI<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const KVTree&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceKVTreeInfoer<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const KVTree&>){
            Resource::add_infoer( new TypedResourceKVTreeInfoerNoAPI<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const std::filesystem::path&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceFileInfoer<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const std::filesystem::path&>){
            Resource::add_infoer( new TypedResourceFileInfoerNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, std::istream&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceStreamInfoer<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, std::istream&>){
            Resource::add_infoer( new TypedResourceStreamInfoerNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const std::string&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceStringInfoer<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const std::string&>){
            Resource::add_infoer( new TypedResourceStringInfoerNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const UrlView&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceUrlInfoer<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const UrlView&>){
            Resource::add_infoer( new TypedResourceUrlInfoerNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const XmlDocument&, const ResourceInfoAPI&>){
            Resource::add_infoer( new TypedResourceXmlInfoer<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<MyInfoPtr, Pred, const XmlDocument&>){
            Resource::add_infoer( new TypedResourceXmlInfoerNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else {
            static_assert( always_false_v<Pred>, "info function is incompatible with known patterns");
        }
    }

    template <typename A>
        template <typename Pred>
    void ResourceIO<A>::add_loader(const ResourceIOSpec&sp, Pred&& fn, const std::source_location& sl)
    {
        if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const ByteArray&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceByteLoader<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const ByteArray&>){
            Resource::add_loader( new TypedResourceByteLoaderNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const json&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceJsonLoader<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const json&>){
            Resource::add_loader( new TypedResourceJsonLoaderNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const KVDocument&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceKVDocumentLoader<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const KVDocument&>){
            Resource::add_loader( new TypedResourceKVDocumentLoaderNoAPI<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const KVTree&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceKVTreeLoader<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const KVTree&>){
            Resource::add_loader( new TypedResourceKVTreeLoaderNoAPI<A,Pred>(sp, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const std::filesystem::path&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceFileLoader<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const std::filesystem::path&>){
            Resource::add_loader( new TypedResourceFileLoaderNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, std::istream&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceStreamLoader<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, std::istream&>){
            Resource::add_loader( new TypedResourceStreamLoaderNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const std::string&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceStringLoader<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const std::string&>){
            Resource::add_loader( new TypedResourceStringLoaderNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const UrlView&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceUrlLoader<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const UrlView&>){
            Resource::add_loader( new TypedResourceUrlLoaderNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const XmlDocument&, const ResourceLoadAPI&>){
            Resource::add_loader( new TypedResourceXmlLoader<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<Ref<A>, Pred, const XmlDocument&>){
            Resource::add_loader( new TypedResourceXmlLoaderNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else {
            static_assert( always_false_v<Pred>, "loader function is incompatible with known patterns");
        }
    }

    template <typename A>
        template <typename Pred>
    void ResourceIO<A>::add_saver(const ResourceIOSpec&sp, Pred&&fn, const std::source_location& sl)
    {
        if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, ByteArray&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceByteSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, ByteArray&>){
            Resource::add_saver( new TypedResourceByteSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, json&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceJsonSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, json&>){
            Resource::add_saver( new TypedResourceJsonSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVDocument&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceKVDocumentSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVDocument&>){
            Resource::add_saver( new TypedResourceKVDocumentSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVTree&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceKVTreeSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVTree&>){
            Resource::add_saver( new TypedResourceKVTreeSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const std::filesystem::path&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceFileSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const std::filesystem::path&>){
            Resource::add_saver( new TypedResourceFileSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::ostream&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceStreamSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::ostream&>){
            Resource::add_saver( new TypedResourceStreamSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::string&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceStringSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::string&>){
            Resource::add_saver( new TypedResourceStringSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const UrlView&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceUrlSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const UrlView&>){
            Resource::add_saver( new TypedResourceUrlSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, XmlDocument&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceXmlSaver<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, XmlDocument&>){
            Resource::add_saver( new TypedResourceXmlSaverNoAPI<A,Pred>(sp, std::move(fn), sl));
            
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, ByteArray&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceByteSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, ByteArray&>){
            Resource::add_saver( new TypedResourceByteSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, json&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceJsonSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, json&>){
            Resource::add_saver( new TypedResourceJsonSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVDocument&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceKVDocumentSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVDocument&>){
            Resource::add_saver( new TypedResourceKVDocumentSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVTree&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceKVTreeSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVTree&>){
            Resource::add_saver( new TypedResourceKVTreeSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const std::filesystem::path&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceFileSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const std::filesystem::path&>){
            Resource::add_saver( new TypedResourceFileSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::ostream&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceStreamSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::ostream&>){
            Resource::add_saver( new TypedResourceStreamSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::string&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceStringSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::string&>){
            Resource::add_saver( new TypedResourceStringSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const UrlView&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceUrlSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const UrlView&>){
            Resource::add_saver( new TypedResourceUrlSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, XmlDocument&, const ResourceSaveAPI&>){
            Resource::add_saver( new TypedResourceXmlSaverBool<A,Pred>(sp, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, XmlDocument&>){
            Resource::add_saver( new TypedResourceXmlSaverBoolNoAPI<A,Pred>(sp, std::move(fn), sl));
        } else {
            static_assert( always_false_v<Pred>, "saver function is incompatible with known patterns");
        } 
    }
}
