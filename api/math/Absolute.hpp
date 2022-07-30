////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>

namespace yq {
    
    /*! \brief Absolute threshhold detection
    
        This becomes true when the error drops beneath the threshhold.
    */
    struct Absolute {
        double      threshhold;
        bool operator()(double error, double) const
        {
            return fabs(error) <= threshhold;
        }
    };
}
