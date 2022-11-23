////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>
#include <math/preamble.hpp>

namespace yq {

    /*! \brief Relative error detection
    
        Used for testing, becomes TRUE when the deviation is small enough in a relative fashion.
    */
    struct Relative {
        double      threshhold;
        bool operator()(double error, double expected) const
        {
            return fabs((error)/expected) <= threshhold;
        }
    };

    constexpr inline bool is_finite(const Relative& v)
    {
        return is_finite(v.threshhold);
    }
}
