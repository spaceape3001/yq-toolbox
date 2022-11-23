////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Store data for corners of 2D box
    */
    template <typename T>
    struct AxCorners2 {
        using component_type    = T;
    
        T   ll;
        T   lh;
        T   hl;
        T   hh;
        
        bool operator==(const AxCorners2&) const noexcept = default;
    };

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const AxCorners2<T>&v)
    {
        return 
            is_finite(v.ll) && 
            is_finite(v.lh) &&
            is_finite(v.hl) && 
            is_finite(v.hh)
        ;
    }
}

