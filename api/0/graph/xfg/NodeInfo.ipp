////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/NodeInfo.hpp>
#include <0/graph/xfg/PinInfo.hpp>

namespace yq::xfg {
    NodeInfo::NodeInfo(std::string_view kname, const ObjectInfo&par, const std::source_location& sl) : 
        ObjectInfo(kname, par, sl)
    {
        set({Flag::NODE, Flag::XFG});
        m_base  = const_cast<NodeInfo*>(to_node(&par));
    }
    
    const NodeInfo::D& NodeInfo::_def(bool all) const 
    { 
        return all ? m_all : m_local; 
    }

    const Meta::LUC<PinInfo>&  NodeInfo::inputs(bool all) const
    {
        return _def(all).inputs;
    }
    
    const Meta::LUC<PinInfo>&  NodeInfo::outputs(bool all) const
    {
        return _def(all).outputs;
    }

    void    NodeInfo::sweep_impl() 
    {
        ObjectInfo::sweep_impl();

        if(m_base){
            m_base -> sweep();
            m_all.inputs += m_base -> m_all.inputs;
            m_all.outputs += m_base -> m_all.outputs;
        }
        
        for(const Meta* m : children()){
            const PinInfo* pin  = to_pin(m);
            if(!pin)
                continue;
            if(pin -> is_input())
                m_local.inputs << pin;
            if(pin -> is_output())
                m_local.outputs << pin;
        }
        
        m_all.inputs += m_local.inputs;
        m_all.outputs += m_local.outputs;
    }

    const NodeInfo*     to_node(const Meta* m)
    {
        return (m && m->is_node() && m->is_xfg()) ? static_cast<const NodeInfo*>(m) : nullptr;
    }
}

