////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/userexpr/forward.hpp>
#include <yq-toolbox/basic/Any.hpp>

namespace yq::expr {
    struct Context {
        u32string_any_map_t     variables;  //!< Variables (used during execution & compilation)
    };
}
