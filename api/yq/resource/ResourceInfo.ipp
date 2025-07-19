////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceInfo.hpp"
#include "ResourceInfoMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::ResourceInfo)

namespace yq {
    ResourceInfoMeta::ResourceInfoMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
    }
    
    ResourceInfo::ResourceInfo()
    {
    }
    
    ResourceInfo::~ResourceInfo()
    {
    }

    void ResourceInfo::init_meta()
    {
        auto w = writer<ResourceInfo>();
        w.abstract();
        w.description("Resource Information");
        w.property("url",   &ResourceInfo::m_url);
        w.property("bytes", &ResourceInfo::m_bytes);
    }
}

