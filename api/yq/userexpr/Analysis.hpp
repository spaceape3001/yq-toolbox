////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/userexpr/forward.hpp>
#include <yq/basic/Any.hpp>

namespace yq::expr {
    struct Analysis {
        u32string_type_map_t    expected;           //!< Expected variable types (used during compilations)
        u32string_set_t         vars_read;     //!< Variable names to be read
        u32string_set_t         vars_written;  //!< Variable names to be read
        u32string_set_t         functions;
        u32string_set_t         constants;
    };
}
