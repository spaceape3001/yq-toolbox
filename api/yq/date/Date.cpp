////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Date.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/date/JulianDay.hpp>
#include <yq/meta/Init.hpp>

#include <ctime>
#include <log4cpp/CategoryStream.hh>
#include <iostream>

namespace yq {
    Date::Date(today_k) : Date()
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

    Date::Date(const JulianDay& jd) : Date(date(jd)) {}
    Date::Date(julian_k, const JulianDay& jd) : Date(date(JULIAN, jd)) {}
    Date::Date(gregorian_k, const JulianDay& jd) : Date(date(GREGORIAN, jd)) {}
    Date::Date(CalendarType ct, const JulianDay& jd) : Date(date(ct, jd)) {}
    
    Date::Date(easter_t, int16_t y) : Date(easter(y)) {}
    Date::Date(julian_k, easter_t, int16_t y) : Date(easter(JULIAN, y)){}
    
    Date::Date(gregorian_k, easter_t, int16_t y) : Date(easter(GREGORIAN, y)){}
    Date::Date(CalendarType ct, easter_t, int16_t y) : Date(easter(ct, y)) {}
    
    bool    Date::is_gregorian() const
    {
        return *this >= GREGORIAN;
    }


    
    //////////////////////////////////////


    Date    date(JulianDay jd)
    {
        return jd.is_gregorian() ? date(GREGORIAN, jd) : date(JULIAN, jd);
    }
    
    Date    date(julian_k, JulianDay jd)
    {
        // from http://www.tondering.dk/claus/cal/julperiod.php
        int b, c;
        int a = jd.jday + 32044;
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
    
    Date    date(gregorian_k, JulianDay jd)
    {
        // from http://www.tondering.dk/claus/cal/julperiod.php
        int b, c;
        int a = jd.jday + 32044;
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
    
    Date    date(CalendarType cal, JulianDay jd)
    {
        switch(cal){
        case CalendarType::Gregorian:
            return date(GREGORIAN, jd);
        case CalendarType::Julian:
            return date(JULIAN, jd);
        default:
            return {};
        }
    }
        
    Date    easter(int16_t year)
    {
        return (year > Date::kGregorianYear) ? easter(GREGORIAN, year) : easter(JULIAN, year);
    }

    Date    easter(julian_k, int16_t y)
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
    
    Date    easter(gregorian_k, int16_t y)
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

    Date    easter(CalendarType cal, int16_t year)
    {
        switch(cal){
        case CalendarType::Gregorian:
            return easter(GREGORIAN, year);
        case CalendarType::Julian:
            return easter(JULIAN, year);
        default:
            return {};
        }
    }

    std::string_view    to_string_view(const Date& v)
    {
        static thread_local char        buffer[64];
        snprintf(buffer,sizeof(buffer), "%04d-%02d-%02d", (int) v.year, (int) v.month, (int) v.day);
        buffer[63] = '\0';
        return buffer;
    }

    Stream&             operator<<(Stream&str, const Date&v)
    {
        return str << to_string_view(v);
    }
}

using namespace yq;

log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&log, const Date&v)
{
    return log << yq::to_string_view(v);
}

std::ostream&               operator<<(std::ostream&str, const Date&v)
{
    return str << yq::to_string_view(v);
}

YQ_TYPE_IMPLEMENT(yq::Date)


static void reg_date()
{
    {
        auto w = writer<Date>();
        w.description("A date (year/month/day)");
        w.property(szYear, &Date::year).description("Year of the date").alias(szYears).alias(szY);
        w.property(szMonth, &Date::month).description("Month of the date (1-12)").alias(szMonths).alias(szM);
        w.property(szDay, &Date::day).description("Day of the date (1-31)").alias(szDays).alias(szD);
    }
}

YQ_INVOKE(reg_date();)

