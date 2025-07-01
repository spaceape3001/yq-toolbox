////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/date/CalendarType.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    struct Date;

    struct JulianDay {
        int32_t     jday    = 0;
        
        static constexpr const int32_t  kGregorian = 2299161;
        
        
        constexpr JulianDay() noexcept = default;
        constexpr JulianDay(int32_t j) noexcept : jday(j) {}
        consteval JulianDay(gregorian_k);
        
        JulianDay(Date);
        JulianDay(gregorian_k, Date);
        JulianDay(julian_k, Date);
        JulianDay(CalendarType, Date);
        
        constexpr auto operator<=>(const JulianDay&) const noexcept = default;
        
        bool        is_gregorian() const;
    };

    consteval JulianDay::JulianDay(gregorian_k) : JulianDay(kGregorian) // 15 Oct 1582
    {
    }
    
    JulianDay    julian_day(Date);
    JulianDay    julian_day(gregorian_k, Date);
    JulianDay    julian_day(julian_k, Date);
    JulianDay    julian_day(CalendarType, Date);
}

YQ_TYPE_DECLARE(yq::JulianDay)
