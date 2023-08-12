////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Date.hpp"
#include "JDay.hpp"
#include <ctime>

namespace yq {
    Date::Date(today_t) : Date()
    {
        time_t      n;
        struct tm   ti;
        time(&n);
        if(localtime_r(&n, &ti)){ [[likely]]
            year    = (int16_t)(ti.tm_year + 1900);
            month   = (uint8_t)(ti.tm_mon + 1);
            day     = (uint8_t) ti.tm_mday;
        }
    }

    Date::Date(JDay jd) 
    {
        if(jd.is_gregorian()){
            *this   = Date(GREGORIAN, jd);
        } else {
            *this   = Date(JULIAN, jd);
        }
    }
    
    Date::Date(gregorian_t, JDay v)
    {
        // from http://www.tondering.dk/claus/cal/julperiod.php
        int b, c;
        int a = v.jday + 32044;
        b   = (4*a+3)/146097;
        c   = a-((146097*b)/4);
        
        int d  = (4*c+3)/1461;
        int e = c-(1461*d)/4;
        int m = (5*e+2)/153;
        
        day     = (uint8_t)(e - (153*m+2)/5+1);
        month   = (uint8_t)(m + 3-12*(m/10));
        year    = (int16_t)(100*b+d-4800+m/10);
        if(year<=0)
            --year;
    }
    
    Date::Date(julian_t, JDay v)
    {
        // from http://www.tondering.dk/claus/cal/julperiod.php
        int b, c;
        b = 0;
        c = v.jday + 32082;
        
        int d  = (4*c+3)/1461;
        int e = c-(1461*d)/4;
        int m = (5*e+2)/153;
        
        day     = (uint8_t)(e - (153*m+2)/5+1);
        month   = (uint8_t)(m + 3-12*(m/10));
        year    = (int16_t)(100*b+d-4800+m/10);
        if(year<=0)
            --year;
    }
    
    Date::Date(Calendar cal, JDay jd)
    {
        switch(cal){
        case Calendar::Gregorian:
            *this = Date(GREGORIAN, jd);
            break;
        case Calendar::Julian:
            *this = Date(JULIAN, jd);
            break;
        default:
            *this   = {};
            break;
        }
    }

    bool    Date::is_gregorian() const
    {
        return *this >= GREGORIAN;
    }

}
