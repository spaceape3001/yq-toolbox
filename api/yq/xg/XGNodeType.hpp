////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    YQ_ENUM(XGNodeType, ,
        Unspecified = 0,   // non deterministic
        Command,
        Decision,
        Always,
        Continue,
        Start,
        Resume,
        Done
    );
    
    bool    is_flow(XGNodeType);
}

YQ_TYPE_DECLARE(yq::XGNodeType)
