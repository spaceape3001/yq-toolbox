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
#include <yq/tensor/Tensor33.hpp>
#include <yq/typedef/eci.hpp>

namespace yq {

    /*! \brief Planet Centered, Inertial coordinate system
    
        While often used in conjunction with Earth (hence "E"), 
        this is a coordinate system centered and inertial to 
        the universe at large; thus a stationary object will
        complete an "orbit" in this system once per rotation.
    */
    struct ECIDomain {
        using keyword_t     = eci_k;
    };
}

YQ_TYPE_DECLARE(yq::ECIAcceleration)
YQ_TYPE_DECLARE(yq::ECIAngularAcceleration)
YQ_TYPE_DECLARE(yq::ECIAngularVelocity)
YQ_TYPE_DECLARE(yq::ECIDisplacement)
YQ_TYPE_DECLARE(yq::ECIForce)
YQ_TYPE_DECLARE(yq::ECIOrientation)
YQ_TYPE_DECLARE(yq::ECIPosition)
YQ_TYPE_DECLARE(yq::ECIRotation)
YQ_TYPE_DECLARE(yq::ECITensor)
YQ_TYPE_DECLARE(yq::ECIVector)
YQ_TYPE_DECLARE(yq::ECIVelocity)


