////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    /*! \brief Greatest common divisor in template parameters
    */
    template <int, int> struct GCD;
    template <int A> struct GCD<A,0> { 
        static constexpr const int VALUE = A;
    };
    
    ;
    template <int A, int B> 
    struct GCD {
       static constexpr const int P         = (A>B)?(A-B):(B-A);
       static constexpr const int VALUE     = GCD<B,P>::VALUE;
    };
}
