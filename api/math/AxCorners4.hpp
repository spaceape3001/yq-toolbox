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
        //! Component type (captures the argument)
        using component_type    = T;
    
        //! Lower-lower-lower-lower corner
        T   llll;

        //! Lower-lower-lower-upper corner
        T   lllh;

        //! Lower-lower-upper-lower corner
        T   llhl;

        //! Lower-lower-upper-upper corner
        T   llhh;

        //! Lower-upper-lower-lower corner
        T   lhll;

        //! Lower-upper-lower-upper corner
        T   lhlh;

        //! Lower-upper-upper-lower corner
        T   lhhl;

        //! Lower-upper-upper-upper corner
        T   lhhh;

        //! Upper-lower-lower-lower corner
        T   hlll;

        //! Upper-lower-lower-upper corner
        T   hllh;

        //! Upper-lower-upper-lower corner
        T   hlhl;

        //! Upper-lower-upper-upper corner
        T   hlhh;

        //! Upper-upper-lower-lower corner
        T   hhll;

        //! Upper-upper-lower-upper corner
        T   hhlh;

        //! Upper-upper-upper-lower corner
        T   hhhl;

        //! Upper-upper-upper-upper corner
        T   hhhh;

        //! Equality operator (defaulted)
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

