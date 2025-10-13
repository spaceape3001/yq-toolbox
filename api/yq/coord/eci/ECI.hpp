////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

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

