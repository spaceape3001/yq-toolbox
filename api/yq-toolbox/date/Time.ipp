////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Time.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/date/Date.hpp>
#include <yq-toolbox/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::Time)

namespace yq {  
    static const Date    kLeapSecondsData[] = {
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
    
    const std::span<const Date>    kLeapSeconds(kLeapSecondsData);
}

using namespace yq;

static void reg_gis_time()
{
    {
        auto w  = writer<Time>();
        w.description("Time (hh:mm:ss.%%)");
        w.property(szHour, &Time::hour).description("Hours to the time (0-23)")
            .alias(szH).alias(szHours);
        w.property(szMinute, &Time::minute).description("Minutes to the time (0-59)")
            .alias(szM).alias(szMin).alias(szMinutes);
        w.property(szSecond, &Time::second).description("Seconds to the time (0-60)")
            .alias(szS).alias(szSec).alias(szSeconds);
        w.property(szPercent, &Time::percent).description("Percentage to the second (0-99)")
            .alias("%");
    }
}

YQ_INVOKE(reg_gis_time();)

