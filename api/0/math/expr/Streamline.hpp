////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/preamble.hpp>

namespace yq::expr {
    //! "Streamlines" the symbol vecotr
    //!
    //! Applies the other methods listed in this header
    std::error_code  streamline(SymVector& syms);

    std::error_code  s_constants(SymVector&);
    std::error_code  s_functions(SymVector&);
    std::error_code  s_signs(SymVector&);
}

