////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/preamble.hpp>

#include <0/graph/xfg/NodeInfo.hpp>
#include <0/graph/xfg/ArrayInputPin.hpp>
#include <0/graph/xfg/ArrayOutputPin.hpp>
#include <0/graph/xfg/SingleInputPin.hpp>
#include <0/graph/xfg/SingleOutputPin.hpp>
#include <0/graph/xfg/VectorConfigInputPin.hpp>
#include <0/graph/xfg/VectorInputPin.hpp>
#include <0/graph/xfg/VectorOutputPin.hpp>

#include <yq-toolbox/basic/Object.hpp>


namespace yq::xfg {

    class Node : public Object {
        YQ_OBJECT_INFO(NodeInfo)
        YQ_OBJECT_DECLARE(Node, Object)
    public:
    
        template <typename T> using In      = SingleInputPin<T>;
        template <typename T> using Out     = SingleOutputPin<T>;

        template <typename T> using VecIn   = VectorInputPin<T>;
        template <typename T> using VecOut  = VectorOutputPin<T>;
        
        template <typename T, typename C> using VecCfgIn = VectorConfigInputPin<T,C>;

        template <typename T, size_t N> using ArrIn   = ArrayInputPin<T, N>;
        template <typename T, size_t N> using ArrOut  = ArrayOutputPin<T, N>;
    };

}

