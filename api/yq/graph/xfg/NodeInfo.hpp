////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/preamble.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/MetaLookup.hpp>

namespace yq::xfg {
    class NodeInfo : public ObjectMeta {
    public:
        template <typename C> class Writer;
        NodeInfo(std::string_view, const ObjectMeta&, const std::source_location& sl = std::source_location::current());
        
        const MetaLookup<PinInfo>&  inputs(bool all=false) const;
        const MetaLookup<PinInfo>&  outputs(bool all=false) const;
    
    protected:
        //! Sweeps on the type (ie gathers properties/methdos)
        virtual void    sweep_impl() override;
    private:

        struct D {
            MetaLookup<PinInfo>     inputs;
            MetaLookup<PinInfo>     outputs;
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
