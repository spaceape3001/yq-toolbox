////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Store data for corners of 1D box
    */
    template <typename T>
    struct AxCorners1 {
    
        //! Component type (capturing the argument)
        using component_type    = T;
    
        //! Lower corner data
        T   l;
        
        //! Upper corner data
        T   h;
        
        //! Equality operator
        constexpr bool operator==(const AxCorners1&) const noexcept = default;
    };

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const AxCorners1<T>&v)
    {
        return is_finite(v.l) && is_finite(v.h);
    }
}

