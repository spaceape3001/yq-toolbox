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
#include <yq/typedef/tenu.hpp>

namespace yq {

    /*! \brief Topographic East North Up
    
        TENU is a coordinate system expanded into flats about a lat/lon, 
        with east being "x", north being "y", and up from HAE/MSL is "z".
    */
    struct TENUDomain {
        using keyword_t     = tenu_k;
    };
}

YQ_TYPE_DECLARE(yq::TENUAcceleration)
YQ_TYPE_DECLARE(yq::TENUAngularAcceleration)
YQ_TYPE_DECLARE(yq::TENUAngularVelocity)
YQ_TYPE_DECLARE(yq::TENUDisplacement)
YQ_TYPE_DECLARE(yq::TENUForce)
YQ_TYPE_DECLARE(yq::TENUOrientation)
YQ_TYPE_DECLARE(yq::TENUPosition)
YQ_TYPE_DECLARE(yq::TENURotation)
YQ_TYPE_DECLARE(yq::TENUTensor)
YQ_TYPE_DECLARE(yq::TENUVector)
YQ_TYPE_DECLARE(yq::TENUVelocity)


