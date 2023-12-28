////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <0/basic/ErrorDB.hpp>

namespace yq {
    namespace errors {
        using degenerate_dimension  = error_db::entry<"Degenerate dimension">;
        using invalid_box           = error_db::entry<"Invalid box">;
    }
}

