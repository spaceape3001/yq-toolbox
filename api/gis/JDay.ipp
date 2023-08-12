////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "JDay.hpp"
#include "Date.hpp"

namespace yq {

    bool        JDay::is_gregorian() const
    {
        return *this >= GREGORIAN;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    JDay    jday(Date d)
    {
        return d.is_gregorian() ? jday(GREGORIAN, d) : jday(JULIAN, d);
    }
    
    JDay    jday(gregorian_t, Date v)
    {
        if(v.year < 0)
            ++v.year;

        int     a   = (14 - v.month) / 12;
        int     y   = v.year + 4800 - a;
        int     m   = v.month + 12*a - 3;
        
        return { (int32_t)( v.day + (153*m+2)/5+365*y+y/4-y/100+y/400-32045) };
    }
    
    JDay    jday(julian_t, Date v)
    {
        if(v.year < 0)
            ++v.year;

        int     a   = (14 - v.month) / 12;
        int     y   = v.year + 4800 - a;
        int     m   = v.month + 12*a - 3;

        return { (int32_t)(v.day + (153*m+2)/5+365*y+y/4-32083) };
    }
    
    JDay    jday(Calendar cal, Date d)
    {
        switch(cal){
        case Calendar::Gregorian:
            return jday(GREGORIAN, d);
        case Calendar::Julian:
            return jday(JULIAN, d);
        default:
            return {};
        }
    }
}
