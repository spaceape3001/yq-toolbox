////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/NodeMeta.hpp>
#include <0/graph/xfg/PinMeta.hpp>

namespace yq::xfg {
    NodeMeta::NodeMeta(std::string_view kname, const ObjectMeta&par, const std::source_location& sl) : 
        ObjectMeta(kname, par, sl)
    {
        set({Flag::NODE, Flag::XFG});
        m_base  = const_cast<NodeMeta*>(to_node(&par));
    }
    
    const NodeMeta::D& NodeMeta::_def(bool all) const 
    { 
        return all ? m_all : m_local; 
    }

    const MetaLookup<PinMeta>&  NodeMeta::inputs(bool all) const
    {
        return _def(all).inputs;
    }
    
    const MetaLookup<PinMeta>&  NodeMeta::outputs(bool all) const
    {
        return _def(all).outputs;
    }

    void    NodeMeta::sweep_impl() 
    {
        ObjectMeta::sweep_impl();

        if(m_base){
            m_base -> sweep();
            m_all.inputs += m_base -> m_all.inputs;
            m_all.outputs += m_base -> m_all.outputs;
        }
        
        for(const Meta* m : children()){
            const PinMeta* pin  = to_pin(m);
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

    const NodeMeta*     to_node(const Meta* m)
    {
        return (m && m->is_node() && m->is_xfg()) ? static_cast<const NodeMeta*>(m) : nullptr;
    }
}

