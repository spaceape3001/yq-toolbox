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
#include <yq/typedef/tned.hpp>

namespace yq {

    /*! \brief Topographic North East Down
    
        TNED is a coordinate system expanded into flats about a lat/lon, 
        with north being "x", east being "y", and down from HAE/MSL is "z".
    */
    struct TNEDDomain {
        using keyword_t     = tned_k;
    };
}

YQ_TYPE_DECLARE(yq::TNEDAcceleration)
YQ_TYPE_DECLARE(yq::TNEDAngularAcceleration)
YQ_TYPE_DECLARE(yq::TNEDAngularVelocity)
YQ_TYPE_DECLARE(yq::TNEDDisplacement)
YQ_TYPE_DECLARE(yq::TNEDForce)
YQ_TYPE_DECLARE(yq::TNEDOrientation)
YQ_TYPE_DECLARE(yq::TNEDPosition)
YQ_TYPE_DECLARE(yq::TNEDRotation)
YQ_TYPE_DECLARE(yq::TNEDTensor)
YQ_TYPE_DECLARE(yq::TNEDVector)
YQ_TYPE_DECLARE(yq::TNEDVelocity)


