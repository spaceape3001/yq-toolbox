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

YQ_TYPE_DECLARE(yq::LNEDAcceleration)
YQ_TYPE_DECLARE(yq::LNEDAngularAcceleration)
YQ_TYPE_DECLARE(yq::LNEDAngularVelocity)
YQ_TYPE_DECLARE(yq::LNEDDisplacement)
YQ_TYPE_DECLARE(yq::LNEDForce)
YQ_TYPE_DECLARE(yq::LNEDOrientation)
YQ_TYPE_DECLARE(yq::LNEDPosition)
YQ_TYPE_DECLARE(yq::LNEDRotation)
YQ_TYPE_DECLARE(yq::LNEDTensor)
YQ_TYPE_DECLARE(yq::LNEDVector)
YQ_TYPE_DECLARE(yq::LNEDVelocity)


