////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/preamble.hpp>
#include <0/meta/ObjectInfo.hpp>

namespace yq::xfg {
    class NodeInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;
        NodeInfo(std::string_view, const ObjectInfo&, const std::source_location& sl = std::source_location::current());
        
        const LUC<PinInfo>&  inputs(bool all=false) const;
        const LUC<PinInfo>&  outputs(bool all=false) const;
    
    protected:
        //! Sweeps on the type (ie gathers properties/methdos)
        virtual void    sweep_impl() override;
    private:

        struct D {
            LUC<PinInfo>     inputs;
            LUC<PinInfo>     outputs;
        };

        //! What's defined on this object
        D               m_local;
        //! What's defiend across all relevant objects
        D               m_all;
        
        NodeInfo*       m_base  = nullptr;           

        const D& _def(bool all) const;
    };
    
    const NodeInfo*     to_node(const Meta*);
}
