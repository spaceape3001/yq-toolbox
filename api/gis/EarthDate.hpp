////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <span>

namespace yq {

    /*! Standard (european) earth-date
    */
    struct EarthDate {
        int16_t     year    = 0; 
        uint8_t     month   = 0;    // 1...12
        uint8_t     day     = 0;    // 1...31
        
        constexpr bool operator==(const EarthDate&) const noexcept = default;
    };
    
    //! Julian day
    struct JulianDay {
        uint32_t    jday    = 0;
        
        constexpr auto operator<=>(const JulianDay&) const noexcept = default;
    };
    
    //! True if gregorian date (per 1582 transition)
    bool                    is_gregorian(EarthDate);

    //! Computes julian day from earth date
    JulianDay               julian_day(EarthDate);
    
    //! Gets today's earth date
    EarthDate               today();
    
    //! Converts julian date to earth date
    EarthDate               date(JulianDay);
    
    //! Table of known leap seconds
    std::span<EarthDate>    leap_seconds();
}
