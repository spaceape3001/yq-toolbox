////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <span>

namespace yq {
    namespace earth {

        /*! Standard (european) earth-date
        */
        struct Date {
            int16_t     year    = 0; 
            uint8_t     month   = 0;    // 1...12
            uint8_t     day     = 0;    // 1...31
            
            constexpr bool operator==(const Date&) const noexcept = default;
        };
        
        //! Julian day
        struct JulianDay {
            uint32_t    jday    = 0;
            
            constexpr auto operator<=>(const JulianDay&) const noexcept = default;
        };
        
        //! True if gregorian date (per 1582 transition)
        bool               is_gregorian(Date);

        //! Computes julian day from earth date
        JulianDay          julian_day(Date);
        
        //! Gets today's earth date
        Date               today();
        
        //! Converts julian date to earth date
        Date               date(JulianDay);
        
        //! Table of known leap seconds
        std::span<Date>    leap_seconds();
    }
}
