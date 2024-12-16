////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "JulianDay.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/date/Date.hpp>
#include <yq/meta/Init.hpp>


namespace yq {

    JulianDay::JulianDay(Date d) : JulianDay(julian_day(d)) {}
    JulianDay::JulianDay(gregorian_t, Date d) : JulianDay(julian_day(GREGORIAN, d)) {}
    JulianDay::JulianDay(julian_t, Date d) : JulianDay(julian_day(JULIAN, d)) {}
    JulianDay::JulianDay(CalendarType ct, Date d) : JulianDay(julian_day(ct, d)) {}

    bool        JulianDay::is_gregorian() const
    {
        return *this >= GREGORIAN;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    JulianDay    julian_day(Date d)
    {
        return d.is_gregorian() ? julian_day(GREGORIAN, d) : julian_day(JULIAN, d);
    }
    
    JulianDay    julian_day(gregorian_t, Date v)
    {
        if(v.year < 0)
            ++v.year;

        int     a   = (14 - v.month) / 12;
        int     y   = v.year + 4800 - a;
        int     m   = v.month + 12*a - 3;
        
        return { (int32_t)( v.day + (153*m+2)/5+365*y+y/4-y/100+y/400-32045) };
    }
    
    JulianDay    julian_day(julian_t, Date v)
    {
        if(v.year < 0)
            ++v.year;

        int     a   = (14 - v.month) / 12;
        int     y   = v.year + 4800 - a;
        int     m   = v.month + 12*a - 3;

        return { (int32_t)(v.day + (153*m+2)/5+365*y+y/4-32083) };
    }
    
    JulianDay    julian_day(CalendarType cal, Date d)
    {
        switch(cal){
        case CalendarType::Gregorian:
            return julian_day(GREGORIAN, d);
        case CalendarType::Julian:
            return julian_day(JULIAN, d);
        default:
            return {};
        }
    }
}

YQ_TYPE_IMPLEMENT(yq::JulianDay)
using namespace yq;

static void reg_julian_day()
{
    {
        auto w = writer<JulianDay>();
        w.description("Date as a julian day");
    }
}

YQ_INVOKE(reg_julian_day();)
