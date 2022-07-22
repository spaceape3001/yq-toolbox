////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>

namespace yq {
    struct Relative {
        double      threshhold;
        bool operator()(double error, double expected) const
        {
            return fabs((error)/expected) <= threshhold;
        }
    };
}
