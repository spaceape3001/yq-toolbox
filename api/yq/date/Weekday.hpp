////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Enum.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>

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
