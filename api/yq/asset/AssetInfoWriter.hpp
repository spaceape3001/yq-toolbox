////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq {
    template <typename C>
    class AssetInfo::Writer : public ObjectInfo::Writer<C> {
    public:
        Writer(AssetInfo* assetInfoPtr) : ObjectInfo::Writer<C>(assetInfoPtr)
        {
        }
        
        Writer(AssetInfo& assetInfoRef) : Writer(&assetInfoRef)
        {
        }
    };
}
