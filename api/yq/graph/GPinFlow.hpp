////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    YQ_ENUM(GPinFlow, ,
        Dead,
        Input,
        In = Input,
        Output,
        Out = Output,
        Dual,
        Bi = Dual
    )
}

YQ_TYPE_DECLARE(yq::GPinFlow)
