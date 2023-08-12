////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {

    struct gregorian_t {};
    static constexpr const gregorian_t  GREGORIAN;
    struct julian_t {};
    static constexpr const julian_t     JULIAN;
    struct today_t {};
    static constexpr const today_t      TODAY;
    

    struct Date;
    struct Time;
    struct JDay;
    
    namespace gis {
    }
    
    namespace ecef {
    }
}

