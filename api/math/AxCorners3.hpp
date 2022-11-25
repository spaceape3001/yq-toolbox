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

        //! Component type (captures the argument)
        using component_type    = T;
    
        //! Lower-lower-lower corner
        T   lll;

        //! Lower-lower-upper corner
        T   llh;

        //! Lower-upper-lower corner
        T   lhl;

        //! Lower-upper-upper corner
        T   lhh;

        //! Upper-lower-lower corner
        T   hll;

        //! Upper-lower-upper corner
        T   hlh;

        //! Upper-upper-lower corner
        T   hhl;

        //! Upper-upper-upper corner
        T   hhh;
        
        //! Equality operator (defaulted)
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

