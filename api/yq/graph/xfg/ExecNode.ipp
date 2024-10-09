////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/xfg/ExecNode.hpp>
#include <0/xfg/ExecNodeInfoWriter.hpp>

namespace yq::xfg {
    ExecNodeInfo::ExecNodeInfo(std::string_view name, const ObjectInfo&par, const std::source_location& sl) : 
        ObjectInfo(name, par, sl)
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
