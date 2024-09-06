////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Enum.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>

namespace yq::chemistry {
    YQ_ENUM( Phase, ,
        Unknown = 0,
        Solid,
        Liquid,
        Gas,
        Plasma
    )
}

YQ_TYPE_DECLARE(yq::chemistry::Phase)
