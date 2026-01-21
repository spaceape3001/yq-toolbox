////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/xfg/ExecNode.hpp>
#include <0/xfg/ExecNodeMetaWriter.hpp>

namespace yq::xfg {
    ExecNodeMeta::ExecNodeMeta(std::string_view name, const ObjectMeta&par, const std::source_location& sl) : 
        ObjectMeta(name, par, sl)
    {
    }


    ////////////////////////////////////////////////////////////////////////////

    ExecNode::ExecNode()
    {
    }
    
    ExecNode::~ExecNode()
    {
        for(ExecPin*p : m_pins)
            delete p;
        m_pins.clear();
    }
}
