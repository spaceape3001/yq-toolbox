////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/InfoBinder.hpp>

namespace yq {
    /*! \brief Executive Flow Graph Namespace
    
        The Executive Flow Graph (XFG) is general execution graph, where the 
        nodes derive from the base node, and have "execute()" methods.
    
    */
    namespace xfg {}
    
    class Object;
}

namespace yq::xfg {
    struct Execute {
        constexpr auto operator<=>(const Execute&) const noexcept = default;
    };

    class Executive;
    class Node;
    class NodeInfo;
    struct PinInfo;

    template <typename>             class SingleInputPin;
    template <typename>             class VectorInputPin;
    template <typename,size_t>      class ArrayInputPin;
    template <typename,typename>    class VectorConfigInputPin;
    
    struct OutputPin;
    template <typename>         class SingleOutputPin;
    template <typename>         class VectorOutputPin;
    template <typename,size_t>  class ArrayOutputPin;
    

    struct VarData {
        void*           data    = nullptr;
        const TypeMeta* type    = nullptr;
    };

    using pin_id_t  = uint16_t;
}

YQ_TYPE_DECLARE(yq::xfg::Execute)

