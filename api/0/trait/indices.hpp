////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  this is taken from https://stackoverflow.com/questions/12765182/c11-variadic-template-function-call-forwarding

namespace yq {
    template <unsigned...> struct indices {};
    template <unsigned N, unsigned... Is> struct indices_gen : indices_gen<N-1,N-1,Is...> {};
    template <unsigned... Is> struct indices_gen<0, Is...> : indices<Is...> {};
}


