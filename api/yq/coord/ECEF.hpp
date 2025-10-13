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
#include <yq/meta/MetaBinder.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/typedef/ecef.hpp>
#include <yq/vector/Quaternion3.hpp>
#include <yq/vector/Vector3.hpp>

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

YQ_TYPE_DECLARE(yq::ECEFAcceleration)
YQ_TYPE_DECLARE(yq::ECEFAngularAcceleration)
YQ_TYPE_DECLARE(yq::ECEFAngularVelocity)
YQ_TYPE_DECLARE(yq::ECEFDisplacement)
YQ_TYPE_DECLARE(yq::ECEFForce)
YQ_TYPE_DECLARE(yq::ECEFOrientation)
YQ_TYPE_DECLARE(yq::ECEFPosition)
YQ_TYPE_DECLARE(yq::ECEFRotation)
YQ_TYPE_DECLARE(yq::ECEFTensor)
YQ_TYPE_DECLARE(yq::ECEFVector)
YQ_TYPE_DECLARE(yq::ECEFVelocity)


