////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <earth/preamble.hpp>

namespace yq {
    /*! \brief General purpose geodetic-style structure
    
        
    */
    template <typename A, typename L>
    struct Geodetic3 {
        A       latitude, longitude;
        L       altitude;
    };
    
}
