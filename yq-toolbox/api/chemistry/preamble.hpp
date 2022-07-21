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
    namespace chemistry {
        YQ_ENUM( Phase, ,
            Unknown = 0,
            Solid,
            Liquid,
            Gas,
            Plasma
        )
    }

}

YQ_TYPE_DECLARE(yq::chemistry::Phase)
