////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

namespace yq {

    /*! \brief Locally Level East/North/Up
    
        LENU is a coordinate system, relative to a particular 3D point is 
        unwrapped in latitude & longitude.  East is "x", North is "y",  and Up 
        is "z".
    */
    struct LENUDomain {
        using keyword_t     = lenu_k;
    };
}

