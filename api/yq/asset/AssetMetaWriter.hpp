////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq {
    template <typename C>
    class AssetMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(AssetMeta* assetInfoPtr) : ObjectMeta::Writer<C>(assetInfoPtr)
        {
        }
        
        Writer(AssetMeta& assetInfoRef) : Writer(&assetInfoRef)
        {
        }
    };
}
