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
    class NodeMeta : public ObjectMeta {
    public:
        template <typename C> class Writer;
        NodeMeta(std::string_view, const ObjectMeta&, const std::source_location& sl = std::source_location::current());
        
        const MetaLookup<PinMeta>&  inputs(bool all=false) const;
        const MetaLookup<PinMeta>&  outputs(bool all=false) const;
    
    protected:
        //! Sweeps on the type (ie gathers properties/methdos)
        virtual void    sweep_impl() override;
    private:

        struct D {
            MetaLookup<PinMeta>     inputs;
            MetaLookup<PinMeta>     outputs;
        };

        //! What's defined on this object
        D               m_local;
        //! What's defiend across all relevant objects
        D               m_all;
        
        NodeMeta*       m_base  = nullptr;           

        const D& _def(bool all) const;
    };
    
    const NodeMeta*     to_node(const Meta*);
}
