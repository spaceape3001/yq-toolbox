////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Enum.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>

namespace yq {
    YQ_ENUM( CalendarType, ,
        None        = 0,
        Julian,
        Gregorian
    )
}
YQ_TYPE_DECLARE(yq::CalendarType)
