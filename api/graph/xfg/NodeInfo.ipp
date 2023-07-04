////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/NodeInfo.hpp>
#include <graph/xfg/PinInfo.hpp>

namespace yq::xfg {
    NodeInfo::NodeInfo(std::string_view kname, const ObjectInfo&par, const std::source_location& sl) : 
        ObjectInfo(kname, par, sl)
    {
        set(Flag::NODE);
        if(par.is_node())
            m_base  = static_cast<NodeInfo*>(const_cast<ObjectInfo*>(&par));
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
}

