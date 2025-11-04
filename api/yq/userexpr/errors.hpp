////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/ErrorDB.hpp>

namespace yq::errors {
    using bad_constant              = error_db::entry<"Bad constant">;
    using bad_function              = error_db::entry<"Bad function">;
    using bad_instruction           = error_db::entry<"Bad instruction">;
    using bad_operator              = error_db::entry<"Bad operator">;
    using bad_userexpr              = error_db::entry<"Bad user expression">;
    using bad_variable              = error_db::entry<"Bad variable">;
    using empty_stack               = error_db::entry<"Empty stack">;
    using incompatible_types        = error_db::entry<"Incompatible types">;
    using mulitple_values           = error_db::entry<"Multiple values remain">;
    using parenthesis_mismatch      = error_db::entry<"Parenthesis mismatch">;
}
