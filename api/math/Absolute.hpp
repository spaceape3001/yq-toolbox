////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>
#include <math/trait/has_is_finite.hpp>

namespace yq {
    
    /*! \brief Absolute threshhold detection
    
        This becomes true when the error drops beneath the threshhold.
    */
    template <typename T=double>
    struct Absolute {
    
        //! Threshold for detection (pass/failure)
        T      threshhold;
        
        //! Does the actual compoutation, passing if the error doesn't exceed the threshhold.
        constexpr bool operator()(T error, T) const noexcept
        {
            return abs(error) <= threshhold;
        }
    };
    YQ_IS_FINITE_1(Absolute, is_finite(v.threshhold) )
}
