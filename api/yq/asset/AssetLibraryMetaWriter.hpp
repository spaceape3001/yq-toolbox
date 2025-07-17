////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetLibrary.hpp>
#include <yq/asset/AssetMetaWriter.hpp>

namespace yq {
    template <typename C>
    class AssetLibraryMeta::Writer : public AssetMeta::Writer<C> {
    public:
        Writer(AssetLibraryMeta* assetInfoPtr) : AssetMeta::Writer<C>(assetInfoPtr), m_myMeta(assetInfoPtr)
        {
        }
        
        Writer(AssetLibraryMeta& assetInfoRef) : Writer(&assetInfoRef)
        {
        }
        
        template <SomeAsset A>
        Writer& asset()
        {
            if(m_myMeta && thread_safe_write()){
                m_myMeta -> m_assets.push_back(&meta<A>());
            }
        
            return *this;
        }
        
    private:
        AssetLibraryMeta* m_myMeta;
    };
}
