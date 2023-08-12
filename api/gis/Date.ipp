////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Date.hpp"
#include "JDay.hpp"
#include <ctime>
#include <cstdio>
#include <log4cpp/CategoryStream.hh>

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

    bool    Date::is_gregorian() const
    {
        return *this >= GREGORIAN;
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    Date    date(JDay jd)
    {
        return jd.is_gregorian() ? date(GREGORIAN, jd) : date(JULIAN, jd);
    }
    
    Date    date(julian_t, JDay v)
    {
        // from http://www.tondering.dk/claus/cal/julperiod.php
        int b, c;
        int a = v.jday + 32044;
        b   = (4*a+3)/146097;
        c   = a-((146097*b)/4);
        
        int d  = (4*c+3)/1461;
        int e = c-(1461*d)/4;
        int m = (5*e+2)/153;
        
        Date    ret;
        ret.day     = (uint8_t)(e - (153*m+2)/5+1);
        ret.month   = (uint8_t)(m + 3-12*(m/10));
        ret.year    = (int16_t)(100*b+d-4800+m/10);
        if(ret.year<=0)
            --ret.year;
        return ret;
    }
    
    Date    date(gregorian_t, JDay v)
    {
        // from http://www.tondering.dk/claus/cal/julperiod.php
        int b, c;
        int a = v.jday + 32044;
        b   = (4*a+3)/146097;
        c   = a-((146097*b)/4);
        
        int d  = (4*c+3)/1461;
        int e = c-(1461*d)/4;
        int m = (5*e+2)/153;
        
        Date    ret;
        ret.day     = (uint8_t)(e - (153*m+2)/5+1);
        ret.month   = (uint8_t)(m + 3-12*(m/10));
        ret.year    = (int16_t)(100*b+d-4800+m/10);
        if(ret.year<=0)
            --ret.year;
        return ret;
    }
    
    Date    date(Calendar cal, JDay jd)
    {
        switch(cal){
        case Calendar::Gregorian:
            return date(GREGORIAN, jd);
        case Calendar::Julian:
            return date(JULIAN, jd);
        default:
            return {};
        }
    }
    
    
    Date    easter(int16_t year)
    {
        return (year > 1582) ? easter(GREGORIAN, year) : easter(JULIAN, year);
    }

    Date    easter(julian_t, int16_t y)
    {
        //  Taken from Astronomical Algorithms 
        int a   = y % 4;
        int b   = y % 7;
        int c   = y % 19;
        int d   = (19*c+15) % 30;
        int e   = (2*a+4*b-d+34) % 7;
        int fg  = (d+e+114);
        int f   = fg / 31;
        int g   = fg % 31;

        return { y, (uint8_t) f, (uint8_t) (g+1) };
    }
    
    Date    easter(gregorian_t, int16_t y)
    {
        //  Taken from Astronomical Algorithms 
        int a = y % 19;
        int b = y / 100;
        int c = y % 100;
        int d = b / 4;
        int e = b % 4;
        int f = (b+8)/25;
        int g = (b - f + 1)/3;
        int h = (19*a+b-d-g+15)%30;
        int i = c / 4;
        int k = c % 4;
        int l = (32+2*e+2*i-h-k)%7;
        int m = (a+11*h+22*l)/451;
        
        int np = h+l-7*m+114;
        int n = np / 31;
        int p = np % 31;
        
        return { y, (uint8_t) n, (uint8_t)(p+1) };
    }

    Date    easter(Calendar cal, int16_t year)
    {
        switch(cal){
        case Calendar::Gregorian:
            return easter(GREGORIAN, year);
        case Calendar::Julian:
            return easter(JULIAN, year);
        default:
            return {};
        }
    }

}

log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&log, const yq::Date&v)
{
    char        buffer[64];
    snprintf(buffer,sizeof(buffer), "{%04d-%02d-%02d}", (int) v.year, (int) v.month, (int) v.day);
    buffer[63] = '\0';
    return log << buffer;
}


