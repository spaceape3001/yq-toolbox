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

    JDay::JDay(Date d)
    {
        *this = d.is_gregorian() ? JDay(GREGORIAN, d) : JDay(JULIAN, d);
    }
    
    JDay::JDay(gregorian_t, Date v)
    {
        if(v.year < 0)
            ++v.year;

        int     a   = (14 - v.month) / 12;
        int     y   = v.year + 4800 - a;
        int     m   = v.month + 12*a - 3;
        
        jday = (int32_t)( v.day + (153*m+2)/5+365*y+y/4-y/100+y/400-32045);
    }
    
    JDay::JDay(julian_t, Date v)
    {
        if(v.year < 0)
            ++v.year;

        int     a   = (14 - v.month) / 12;
        int     y   = v.year + 4800 - a;
        int     m   = v.month + 12*a - 3;

        jday    = (int32_t)(v.day + (153*m+2)/5+365*y+y/4-32083);
    }
    
    JDay::JDay(Calendar cal, Date d)
    {
        switch(cal){
        case Calendar::Gregorian:
            *this = JDay(GREGORIAN, d);
            break;
        case Calendar::Julian:
            *this = JDay(JULIAN, d);
            break;
        default:
            jday        = 0;
            break;
        }
    }
}
