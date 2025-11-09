////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TypeInfo.hpp"
#include <yq/meta/TypeMeta.hpp>

namespace yq::lua {
    TypeInfo::TypeInfo(const TypeMeta& tm) : ModuleInfo(tm.name().data()), m_meta(tm)
    {
    }
    
    TypeInfo::~TypeInfo() = default;
}
