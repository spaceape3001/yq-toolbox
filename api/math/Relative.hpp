////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_RELATIVE_HPP 1

#include <cmath>

namespace yq {

    /*! \brief Relative error detection
    
        Used for testing, becomes TRUE when the deviation is small enough in a relative fashion.
    */
    struct Relative {
    
        //! Threshhold of the relative
        double      threshhold;
        
        //! Evaluation operator
        bool operator()(double error, double expected) const
        {
            return fabs((error)/expected) <= threshhold;
        }
    };
}
