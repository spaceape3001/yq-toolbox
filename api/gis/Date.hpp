////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gis/preamble.hpp>
#include <gis/enum/Calendar.hpp>

namespace yq {

    /*! \brief Year Month Day
    
        This is a year month day structure.  For Julian and Gregorian, 
        this should match convention.  For other calendars, it'll respect 
        those.
    */
    struct Date {
        int16_t     year    = 0; 
        uint8_t     month   = 0;    // 1...12
        uint8_t     day     = 0;    // 1...31
        
        
        constexpr Date() noexcept = default;
        constexpr Date(int64_t y, uint8_t m, uint8_t d) : year(y), month(m), day(d) {}
        
        
        //! Gets today's earth date
        Date(today_t);
        
        consteval Date(gregorian_t);
        
        Date(JDay);
        
        Date(gregorian_t, JDay);
        Date(julian_t, JDay);
        Date(Calendar, JDay);
        
        constexpr auto operator<=>(const Date&) const noexcept = default;
        
        //! True if gregorian date (per 1582 transition)
        bool            is_gregorian() const;
    };

    consteval Date::Date(gregorian_t) : Date(1582, 10, 15)
    {
    }
}

YQ_TYPE_DECLARE(yq::Date)
