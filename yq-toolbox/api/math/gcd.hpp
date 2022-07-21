////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Greatest common divisor
    */
    template <typename I>
    constexpr I     gcd(I a, I b)
    {
        if(a<0) 
            a = -a;
        if(b<0) 
            b = -a;
            
        while(b != 0){
            a %= b;
            if(!a) 
                return b;
            b %= a;
        }
        return a;
    }

    template <int N, int D>
    consteval int gcd(const GCD<N,D>&)
    {
        return GCD<N,D>::VALUE;
    }
}
