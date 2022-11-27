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
    
        //! Component type (captures the argument)
        using component_type    = T;
    
        //! Lower-lower corner
        T   ll;

        //! Lower-upper corner
        T   lh;

        //! Upper-lower corner
        T   hl;

        //! Upper-upper corner
        T   hh;
        
        //! Equality operator (defaulted)
        constexpr bool operator==(const AxCorners2&) const noexcept = default;
    };
}

