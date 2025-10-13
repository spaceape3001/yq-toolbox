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
#include <yq/typedef/ecef.hpp>

namespace yq {

    /*! \brief Planet Centered, Planet Fixed coordinate system
    
        While often used in conjunction with Earth (hence "E"), 
        this is a coordinate system centered and fixed to the
        rotating body. 
    */
    struct ECEFDomain {
        using keyword_t     = ecef_k;
    };
}
