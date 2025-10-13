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
#include <yq/typedef/bnsd.hpp>

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

YQ_TYPE_DECLARE(yq::BNSDAcceleration)
YQ_TYPE_DECLARE(yq::BNSDAngularAcceleration)
YQ_TYPE_DECLARE(yq::BNSDAngularVelocity)
YQ_TYPE_DECLARE(yq::BNSDDisplacement)
YQ_TYPE_DECLARE(yq::BNSDForce)
YQ_TYPE_DECLARE(yq::BNSDOrientation)
YQ_TYPE_DECLARE(yq::BNSDPosition)
YQ_TYPE_DECLARE(yq::BNSDRotation)
YQ_TYPE_DECLARE(yq::BNSDTensor)
YQ_TYPE_DECLARE(yq::BNSDVector)
YQ_TYPE_DECLARE(yq::BNSDVelocity)


