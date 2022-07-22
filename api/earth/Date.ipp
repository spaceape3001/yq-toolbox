////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Date.hpp"
#include <time.h>

namespace yq {
    namespace earth {
        
        namespace {
        
            //  obviously an ever growing list of dates, added whenever one's been declared
            static Date    kLeapSeconds[] = {
                { 1972, 6, 30 },
                { 1972, 12, 31 },
                { 1973, 12, 31 },
                { 1974, 12, 31 },
                { 1975, 12, 31 },
                { 1976, 12, 31 },
                { 1977, 12, 31 },
                { 1978, 12, 31 },
                { 1979, 12, 31 },
                { 1981, 6, 30 },
                { 1982, 6, 30 },
                { 1983, 6, 30 },
                { 1985, 6, 30 },
                { 1987, 12, 31 },
                { 1989, 12, 31 },
                { 1990, 12, 31 },
                { 1992, 6, 30 },
                { 1993, 6, 30 },
                { 1994, 6, 30 },
                { 1995, 12, 31 },
                { 1997, 6, 30 },
                { 1998, 12, 31 },
                { 2005, 12, 31 },
                { 2008, 12, 31 },
                { 2012, 6, 30 },
                { 2015, 6, 30 },
                { 2016, 12, 31 }
            };
        }


        bool                    is_gregorian(Date v)
        {
            if(v.year > 1582)
                return true;
            if(v.year < 1582)
                return false;
            if(v.month > 10)
                return true;
            if(v.month < 10)
                return false;
            if(v.day >= 15)
                return true;    //  and we'll ignore the 10 day gap
            return false;
        }
        
        JulianDay               julian_day(Date v)
        {
            if(v.year < 0)
                ++v.year;

            int     a   = (14 - v.month) / 12;
            int     y   = v.year + 4800 - a;
            int     m   = v.month + 12*a - 3;
            if(is_gregorian(v)){
                return { (uint32_t)( v.day + (153*m+2)/5+365*y+y/4-y/100+y/400-32045) };
            } else {
                return { (uint32_t)(v.day + (153*m+2)/5+365*y+y/4-32083) };
            }
        }
        
        Date               date(JulianDay v)
        {
            // from http://www.tondering.dk/claus/cal/julperiod.php
            int b, c;
            Date    ret;
            if(v.jday >= 2299161){
                int a = v.jday + 32044;
                b   = (4*a+3)/146097;
                c   = a-((146097*b)/4);
            } else {
                b = 0;
                c = v.jday + 32082;
            }
            
            int d  = (4*c+3)/1461;
            int e = c-(1461*d)/4;
            int m = (5*e+2)/153;
            
            ret.day     = (uint8_t)(e - (153*m+2)/5+1);
            ret.month   = (uint8_t)(m + 3-12*(m/10));
            ret.year    = (int16_t)(100*b+d-4800+m/10);
            if(ret.year<=0)
                --ret.year;
            return ret;
        }
        

        std::span<Date>    leap_seconds()
        {
            static const std::span<Date>   s_ret(kLeapSeconds);
            return s_ret;
        }

        Date               today()
        {
            time_t      n;
            struct tm   ti;
            time(&n);
            if(localtime_r(&n, &ti)){ [[likely]]
                return { (int16_t)(ti.tm_year + 1900), (uint8_t)(ti.tm_mon + 1), (uint8_t) ti.tm_mday };
            } else
                return {};
            
        }
        
    }
}

