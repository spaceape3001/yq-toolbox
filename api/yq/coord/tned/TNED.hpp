////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

namespace yq {

    /*! \brief Topographic North East Down
    
        TNED is a coordinate system expanded into flats about a lat/lon, 
        with north being "x", east being "y", and down from HAE/MSL is "z".
    */
    struct TNEDDomain {
        using keyword_t     = tned_k;
    };
}
