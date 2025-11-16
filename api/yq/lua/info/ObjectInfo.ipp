////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ObjectInfo.hpp"
#include <yq/meta/ObjectMeta.hpp>

namespace yq::lua {
    ObjectInfo::ObjectInfo(const ObjectMeta& om) : ModuleInfo(std::string(om.stem())), m_meta(om)
    {
    }
    
    ObjectInfo::~ObjectInfo() = default;
}
