////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Store data for corners of 3D box
    */
    template <typename T>
    struct AxCorners3 {
        using component_type    = T;
    
        T   lll;
        T   llh;
        T   lhl;
        T   lhh;
        T   hll;
        T   hlh;
        T   hhl;
        T   hhh;
        
        bool operator==(const AxCorners3&) const noexcept = default;
    };

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const AxCorners3<T>&v)
    {
        return 
            is_finite(v.lll) && 
            is_finite(v.llh) &&
            is_finite(v.lhl) && 
            is_finite(v.lhh) &&
            is_finite(v.hll) && 
            is_finite(v.hlh) &&
            is_finite(v.hhl) && 
            is_finite(v.hhh)
        ;
    }
}

