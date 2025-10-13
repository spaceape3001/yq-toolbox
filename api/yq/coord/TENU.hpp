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
