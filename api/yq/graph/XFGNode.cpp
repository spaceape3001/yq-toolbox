////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "XFGNode.hpp"
#include "XFGNodeInfoWriter.hpp"

namespace yq::xfg {
    XFGNodeInfo::XFGNodeInfo(std::string_view sv, ObjectMeta& obj, const std::source_location& sl) : 
        ObjectMeta(sv, obj, sl)
    {
    }
    
    void    XFGNodeInfo::sweep_impl() 
    {
    }

    const XFGNodeInfo::D& XFGNodeInfo::_def(bool all) const 
    { 
        return all ? m_all : m_local; 
    }
    
}

YQ_OBJECT_IMPLEMENT(yq::XFGNode)

