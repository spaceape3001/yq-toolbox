////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetInfo.hpp"
#include "AssetInfoMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::AssetInfo)

namespace yq {
    AssetInfoMeta::AssetInfoMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
    }
    
    AssetInfo::AssetInfo()
    {
    }
    
    AssetInfo::~AssetInfo()
    {
    }

    void AssetInfo::init_meta()
    {
        auto w = writer<AssetInfo>();
        w.abstract();
        w.description("Asset Information");
        w.property("url",   &AssetInfo::m_url);
        w.property("bytes", &AssetInfo::m_bytes);
    }
}

