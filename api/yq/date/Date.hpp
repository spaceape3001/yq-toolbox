////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/date/CalendarType.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <iosfwd>

namespace log4cpp { class CategoryStream; }

namespace yq {
    class Stream;
    struct JulianDay;

    /*! \brief Year Month Day
    
        This is a year month day structure.  For Julian and Gregorian, 
        this should match convention.  For other calendars, it'll respect 
        those.
    */
    struct Date {
        int16_t     year    = 0; 
        uint8_t     month   = 0;    // 1...12
        uint8_t     day     = 0;    // 1...31
        
        static constexpr const int16_t  kGregorianYear   = 1582;
        static constexpr const uint8_t  kGregorianMonth  = 10;
        static constexpr const uint8_t  kGregorianDay    = 15;

        constexpr Date() noexcept = default;
        constexpr Date(int64_t y, uint8_t m, uint8_t d) : year(y), month(m), day(d) {}
        
        Date(const JulianDay&);
        Date(julian_k, const JulianDay&);
        Date(gregorian_k, const JulianDay&);
        Date(CalendarType, const JulianDay&);
        
        Date(easter_t, int16_t);
        Date(julian_k, easter_t, int16_t);
        Date(gregorian_k, easter_t, int16_t);
        Date(CalendarType, easter_t, int16_t);
        
        //! Gets today's earth date
        Date(today_k);
        
        consteval Date(gregorian_k);
        

        constexpr auto operator<=>(const Date&) const noexcept = default;
        
        //! True if gregorian date (per 1582 transition)
        bool            is_gregorian() const;
        
    };

    consteval Date::Date(gregorian_k) : Date(kGregorianYear, kGregorianMonth, kGregorianDay)
    {
    }
        
    Date                date(JulianDay);
    Date                date(julian_k, JulianDay);
    Date                date(gregorian_k, JulianDay);
    Date                date(CalendarType, JulianDay);
    
    Date                easter(int16_t);
    Date                easter(julian_k, int16_t);
    Date                easter(gregorian_k, int16_t);
    Date                easter(CalendarType, int16_t);

    //! Puts date out as string view (copy to preserve, it's thread-local)
    std::string_view    to_string_view(const Date&);

    Stream&             operator<<(Stream&, const Date&);
}

log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&, const yq::Date&);
std::ostream&               operator<<(std::ostream&, const yq::Date&);

YQ_TYPE_DECLARE(yq::Date)

