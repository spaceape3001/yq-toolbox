////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <basic/Enum.hpp>
#include <basic/meta/InfoBinder.hpp>

namespace yq {
    namespace earth {
        struct Date;
        struct JulianDay;
        struct Time;
        
        YQ_ENUM( Weekday, ,
            Sunday  = 1,
            Monday,
            Tuesday,
            Wednesday,
            Thursday,
            Friday,
            Saturday
        );
    }
}

YQ_TYPE_DECLARE(yq::earth::Weekday)
