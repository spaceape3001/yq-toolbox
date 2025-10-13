////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/keywords.hpp>
#include <yq/units.hpp>
#include <yq/coord/DOrientation.hpp>
#include <yq/coord/DPosition.hpp>
#include <yq/coord/DTensor.hpp>
#include <yq/coord/DVector.hpp>
#include <yq/typedef/bsnu.hpp>

namespace yq {

    /*! \brief Body Starboard/Nose/Up
    
        This is a coordinate system whereas the body's "nose" or bow is forward 
        in "y",  "starboard" or right is in "x", thus "up" is in "z" so that 
        the right hand rule applies.
    */
    struct BSNUDomain {
        using keyword_t     = bsnu_k;
        
    };
}
