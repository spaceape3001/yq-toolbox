////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/preamble.hpp>

#include <graph/xfg/NodeInfo.hpp>
#include <graph/xfg/ArrayInputPin.hpp>
#include <graph/xfg/ArrayOutputPin.hpp>
#include <graph/xfg/SingleInputPin.hpp>
#include <graph/xfg/SingleOutputPin.hpp>
#include <graph/xfg/VectorInputPin.hpp>
#include <graph/xfg/VectorOutputPin.hpp>

#include <basic/Object.hpp>


namespace yq::xfg {

    class Node : public Object {
        YQ_OBJECT_INFO(NodeInfo)
        YQ_OBJECT_DECLARE(Node, Object)
    public:
    
        template <typename T> using In      = SingleInputPin<T>;
        template <typename T> using Out     = SingleOutputPin<T>;

        template <typename T> using VecIn   = VectorInputPin<T>;
        template <typename T> using VecOut  = VectorOutputPin<T>;

        template <typename T, size_t N> using ArrIn   = ArrayInputPin<T, N>;
        template <typename T, size_t N> using ArrOut  = ArrayOutputPin<T, N>;
    };

}

