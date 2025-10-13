////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

namespace yq {

    /*! \brief Locally Level North/East/Down
    
        LNED is a coordinate system, relative to a particular 3D point is 
        unwrapped in latitude & longitude.  North is "x", East is "y",  and Down
        is "z".
    */
    struct LNEDDomain {
        using keyword_t     = lned_k;
    };
}

