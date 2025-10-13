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
#include <yq/typedef/lned.hpp>

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
