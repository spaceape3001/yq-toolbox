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
    struct Absolute {
    
        //! Threshold for detection (pass/failure)
        double      threshhold;
        
        //! Does the actual compoutation, passing if the error doesn't exceed the threshhold.
        bool operator()(double error, double) const
        {
            return fabs(error) <= threshhold;
        }
        
        YQ_IS_FINITE(Absolute, is_finite(v.threshhold) )
    };
}
