////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <math/preamble.hpp>

namespace yq {

    struct easter_t {};
    struct gregorian_t {};
    struct julian_t {};
    struct today_t {};

    static constexpr const easter_t     EASTER;
    static constexpr const gregorian_t  GREGORIAN;
    static constexpr const julian_t     JULIAN;
    static constexpr const today_t      TODAY;

    struct Date;
    struct Time;
    struct JDay;
    
    template <typename A>
    struct Geodetic2;
    
    template <typename A, typename L>   struct Geodetic3;
        
    using Geodetic2R    = Geodetic2<unit::Radian>;
    using Geodetic2D    = Geodetic2<unit::Degree>;
    using Geodetic3RM   = Geodetic3<unit::Radian, unit::Meter>;
    using Geodetic3RF   = Geodetic3<unit::Radian, unit::Foot>;
    using Geodetic3DM   = Geodetic3<unit::Degree, unit::Meter>;
    using Geodetic3DF   = Geodetic3<unit::Degree, unit::Foot>;
    
    namespace gis {
    }
    
    namespace ecef {
    }
}

