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
#include <yq/typedef/lenu.hpp>

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

YQ_TYPE_DECLARE(yq::LENUAcceleration)
YQ_TYPE_DECLARE(yq::LENUAngularAcceleration)
YQ_TYPE_DECLARE(yq::LENUAngularVelocity)
YQ_TYPE_DECLARE(yq::LENUDisplacement)
YQ_TYPE_DECLARE(yq::LENUForce)
YQ_TYPE_DECLARE(yq::LENUOrientation)
YQ_TYPE_DECLARE(yq::LENUPosition)
YQ_TYPE_DECLARE(yq::LENURotation)
YQ_TYPE_DECLARE(yq::LENUTensor)
YQ_TYPE_DECLARE(yq::LENUVector)
YQ_TYPE_DECLARE(yq::LENUVelocity)


