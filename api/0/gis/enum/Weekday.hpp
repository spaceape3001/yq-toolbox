////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>
#include <0/meta/InfoBinder.hpp>

namespace yq {
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

YQ_TYPE_DECLARE(yq::Weekday)
