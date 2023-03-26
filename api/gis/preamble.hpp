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
    struct EarthDate;
    struct JulianDay;
    struct EarthTime;
    
    YQ_ENUM( Weekday, ,
        Sunday  = 1,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    );
    
    enum class CubeSurface {
        None = 0,
        XPositive,
        YPositive,
        ZPositive,
        XNegative,
        YNegative,
        ZNegative
    };
    
    namespace gis {
    }
    
    namespace ecef {
    }
}

YQ_TYPE_DECLARE(yq::Weekday)
