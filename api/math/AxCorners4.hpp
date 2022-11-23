////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Store data for corners of 4D box
    */
    template <typename T>
    struct AxCorners4 {
        using component_type    = T;
    
        T   llll;
        T   lllh;
        T   llhl;
        T   llhh;
        T   lhll;
        T   lhlh;
        T   lhhl;
        T   lhhh;

        T   hlll;
        T   hllh;
        T   hlhl;
        T   hlhh;
        T   hhll;
        T   hhlh;
        T   hhhl;
        T   hhhh;

        bool operator==(const AxCorners4&) const noexcept = default;
    };

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const AxCorners4<T>&v)
    {
        return 
            is_finite(v.llll) && 
            is_finite(v.lllh) &&
            is_finite(v.llhl) && 
            is_finite(v.llhh) &&
            is_finite(v.lhll) && 
            is_finite(v.lhlh) &&
            is_finite(v.lhhl) && 
            is_finite(v.lhhh) &&
            is_finite(v.hlll) && 
            is_finite(v.hllh) &&
            is_finite(v.hlhl) && 
            is_finite(v.hlhh) &&
            is_finite(v.hhll) && 
            is_finite(v.hhlh) &&
            is_finite(v.hhhl) && 
            is_finite(v.hhhh)
        ;
    }
}

