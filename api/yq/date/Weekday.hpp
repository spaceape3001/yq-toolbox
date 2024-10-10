////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/meta/InfoBinder.hpp>

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
