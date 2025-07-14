////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/asset/AssetByteDriver.hxx>
#include <yq/asset/AssetFileDriver.hxx>
#include <yq/asset/AssetJsonDriver.hxx>
#include <yq/asset/AssetKVDocumentDriver.hxx>
#include <yq/asset/AssetKVTreeDriver.hxx>
#include <yq/asset/AssetStreamDriver.hxx>
#include <yq/asset/AssetStringDriver.hxx>
#include <yq/asset/AssetUrlDriver.hxx>
#include <yq/asset/AssetXmlDriver.hxx>
#include <yq/trait/always_false.hpp>
#include <type_traits>

namespace yq {
    template <typename A>
        template <typename Pred>
    void AssetIO<A>::add_infoer(const AssetIOSpec&sp, Pred&&fn, const std::source_location& sl)
    {
        if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const ByteArray&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetByteInfoer<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const ByteArray&>){
            Asset::add_loader( new TypedAssetByteInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const json&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetJsonInfoer<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const json&>){
            Asset::add_loader( new TypedAssetJsonInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const KVDocument&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetKVDocumentInfoer<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const KVDocument&>){
            Asset::add_loader( new TypedAssetKVDocumentInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const KVTree&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetKVTreeInfoer<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const KVTree&>){
            Asset::add_loader( new TypedAssetKVTreeInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const std::filesystem::path&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetFileInfoer<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const std::filesystem::path&>){
            Asset::add_loader( new TypedAssetFileInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, std::istream&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetStreamInfoer<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, std::istream&>){
            Asset::add_loader( new TypedAssetStreamInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const std::string&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetStringInfoer<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const std::string&>){
            Asset::add_loader( new TypedAssetStringInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const UrlView&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetUrlInfoer<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const UrlView&>){
            Asset::add_loader( new TypedAssetUrlInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const XmlDocument&, const AssetInfoAPI&>){
            Asset::add_loader( new TypedAssetXmlInfoer<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<typename A::MyInfo*, Pred, const XmlDocument&>){
            Asset::add_loader( new TypedAssetXmlInfoerNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else {
            static_assert( always_false_v<Pred>, "info function is incompatible with known patterns");
        }
    }

    template <typename A>
        template <typename Pred>
    void AssetIO<A>::add_loader(const AssetIOSpec&sp, Pred&& fn, const std::source_location& sl)
    {
        if constexpr (std::is_invocable_r_v<A*, Pred, const ByteArray&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetByteLoader<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const ByteArray&>){
            Asset::add_loader( new TypedAssetByteLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const json&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetJsonLoader<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const json&>){
            Asset::add_loader( new TypedAssetJsonLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const KVDocument&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetKVDocumentLoader<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const KVDocument&>){
            Asset::add_loader( new TypedAssetKVDocumentLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const KVTree&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetKVTreeLoader<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const KVTree&>){
            Asset::add_loader( new TypedAssetKVTreeLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.recursive, sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const std::filesystem::path&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetFileLoader<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const std::filesystem::path&>){
            Asset::add_loader( new TypedAssetFileLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, std::istream&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetStreamLoader<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, std::istream&>){
            Asset::add_loader( new TypedAssetStreamLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const std::string&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetStringLoader<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const std::string&>){
            Asset::add_loader( new TypedAssetStringLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const UrlView&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetUrlLoader<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const UrlView&>){
            Asset::add_loader( new TypedAssetUrlLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const XmlDocument&, const AssetLoadAPI&>){
            Asset::add_loader( new TypedAssetXmlLoader<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<A*, Pred, const XmlDocument&>){
            Asset::add_loader( new TypedAssetXmlLoaderNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else {
            static_assert( always_false_v<Pred>, "loader function is incompatible with known patterns");
        }
    }

    template <typename A>
        template <typename Pred>
    void AssetIO<A>::add_saver(const AssetIOSpec&sp, Pred&&fn, const std::source_location& sl)
    {
        if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, ByteArray&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetByteSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, ByteArray&>){
            Asset::add_saver( new TypedAssetByteSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, json&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetJsonSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, json&>){
            Asset::add_saver( new TypedAssetJsonSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVDocument&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetKVDocumentSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVDocument&>){
            Asset::add_saver( new TypedAssetKVDocumentSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVTree&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetKVTreeSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, KVTree&>){
            Asset::add_saver( new TypedAssetKVTreeSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const std::filesystem::path&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetFileSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const std::filesystem::path&>){
            Asset::add_saver( new TypedAssetFileSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::ostream&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetStreamSaver<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::ostream&>){
            Asset::add_saver( new TypedAssetStreamSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::string&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetStringSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, std::string&>){
            Asset::add_saver( new TypedAssetStringSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const UrlView&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetUrlSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, const UrlView&>){
            Asset::add_saver( new TypedAssetUrlSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, XmlDocument&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetXmlSaver<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<std::error_code, Pred, const A&, XmlDocument&>){
            Asset::add_saver( new TypedAssetXmlSaverNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
            
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, ByteArray&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetByteSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, ByteArray&>){
            Asset::add_saver( new TypedAssetByteSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, json&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetJsonSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, json&>){
            Asset::add_saver( new TypedAssetJsonSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVDocument&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetKVDocumentSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVDocument&>){
            Asset::add_saver( new TypedAssetKVDocumentSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVTree&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetKVTreeSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, KVTree&>){
            Asset::add_saver( new TypedAssetKVTreeSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const std::filesystem::path&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetFileSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const std::filesystem::path&>){
            Asset::add_saver( new TypedAssetFileSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::ostream&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetStreamSaverBool<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::ostream&>){
            Asset::add_saver( new TypedAssetStreamSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sp.binary, sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::string&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetStringSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, std::string&>){
            Asset::add_saver( new TypedAssetStringSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const UrlView&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetUrlSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, const UrlView&>){
            Asset::add_saver( new TypedAssetUrlSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, XmlDocument&, const AssetSaveAPI&>){
            Asset::add_saver( new TypedAssetXmlSaverBool<A,Pred>(sp.extensions, std::move(fn), sl));
        } else if constexpr (std::is_invocable_r_v<bool, Pred, const A&, XmlDocument&>){
            Asset::add_saver( new TypedAssetXmlSaverBoolNoAPI<A,Pred>(sp.extensions, std::move(fn), sl));
        } else {
            static_assert( always_false_v<Pred>, "saver function is incompatible with known patterns");
        } 
    }
}
