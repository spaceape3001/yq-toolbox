////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "XFGNode.hpp"
#include "XFGNodeMetaWriter.hpp"

namespace yq::xfg {
    XFGNodeMeta::XFGNodeMeta(std::string_view sv, ObjectMeta& obj, const std::source_location& sl) : 
        ObjectMeta(sv, obj, sl)
    {
    }
    
    void    XFGNodeMeta::sweep_impl() 
    {
    }

    const XFGNodeMeta::D& XFGNodeMeta::_def(bool all) const 
    { 
        return all ? m_all : m_local; 
    }
    
}

YQ_OBJECT_IMPLEMENT(yq::XFGNode)

