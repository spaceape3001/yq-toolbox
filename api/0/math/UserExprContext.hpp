////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <0/basic/Any.hpp>
#include <0/basic/Stack.hpp>

namespace yq::expr {
    struct Context {
        u32string_any_map_t     variables;  //!< Variables (used during execution & compilation)
    };
    
    struct Analysis {
        u32string_type_map_t    expected;           //!< Expected variable types (used during compilations)
        u32string_set_t         vars_read;     //!< Variable names to be read
        u32string_set_t         vars_written;  //!< Variable names to be read
        u32string_set_t         functions;
        u32string_set_t         constants;
    };
}
