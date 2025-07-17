////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetInfo.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq {
    template <typename C>
    class AssetInfoMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(AssetInfoMeta* assetInfoPtr) : ObjectMeta::Writer<C>(assetInfoPtr), m_myMeta(assetInfoPtr)
        {
        }
        
        Writer(AssetInfoMeta& assetInfoRef) : Writer(&assetInfoRef)
        {
        }
        
        template <typename A>
        Writer& asset()
        {
            if(m_myMeta && Meta::thread_safe_write() && !m_myMeta->m_asset)
                m_myMeta->m_asset   = &meta<A>();
            return *this;
        }
        
    private:
        AssetInfoMeta* m_myMeta;
    };
}
