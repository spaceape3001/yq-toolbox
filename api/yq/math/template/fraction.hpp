////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/math/template/gcd.hpp>

namespace yq {
    //  This is a FIXED fraction
    template <int N, int D=(int) 1>
    struct FRACTION {
        static_assert(D != 0, "Denominator can never be zero!");
        
        static constexpr const int    NUM     = N;
        static constexpr const int    DEN     = D;
        static constexpr const int    CF      = GCD<N,D>::VALUE;
        static constexpr const int    PNUM    = N / CF;
        static constexpr const int    PDEN    = D / CF;
        static constexpr const int    SNUM = (D<0)?-PNUM:PNUM;
        static constexpr const int    SDEN = (D<0)?-PDEN:PDEN;
        
        using Simplified    = FRACTION<SNUM,SDEN>;
        
        template <class F>
        using Add = typename FRACTION<N*F::DEN+F::NUM*D,D*F::DEN>::Simplified;

        template <class F>
        using Sub = typename FRACTION<N*F::DEN-F::NUM*D,D*F::DEN>::Simplified;
        
        template <class F>
        using Mult = typename FRACTION<N*F::NUM,D*F::DEN>::Simplified;
        
        template <class F>
        using Div = typename FRACTION<N*F::DEN,D*F::NUM>::Simplified;
    };
}
