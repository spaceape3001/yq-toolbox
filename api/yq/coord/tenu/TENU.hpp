////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

namespace yq {

    /*! \brief Topographic East North Up
    
        TENU is a coordinate system expanded into flats about a lat/lon, 
        with east being "x", north being "y", and up from HAE/MSL is "z".
    */
    struct TENUDomain {
        using keyword_t     = tenu_k;
    };
}
