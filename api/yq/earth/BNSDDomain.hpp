////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

namespace yq {

    /*! \brief Body Nose/Starboard/Down
    
        Used often in airplanes, it's a coordinate system whereas the body's 
        "nose" or bow is forward in "x",  "starboard" or right is in "y", thus 
        "down" is in "z" so that the right hand rule applies.
    */
    struct BNSDDomain {
        using keyword_t     = ecef_k;
    };
}
