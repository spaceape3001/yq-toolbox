////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TypeInfo.hpp"
#include <yq/meta/TypeMeta.hpp>

namespace yq::lua {
    TypeInfo::TypeInfo(const TypeMeta& tm) : ModuleInfo(std::string(tm.stem())), m_meta(tm)
    {
    }
    
    TypeInfo::~TypeInfo() = default;
}
