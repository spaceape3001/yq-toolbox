////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceConverter.hpp"

namespace yq {    
    ResourceConverter::ResourceConverter(const ResourceMeta&src, const ResourceMeta&tgt, const std::source_location&loc) :
        m_source(src), m_target(tgt), m_location(loc)
    {
    }

    ResourceConverter::~ResourceConverter()
    {
    }
}
