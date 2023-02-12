////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

// using example
// https://pureprogrammer.org/wp/2021/12/19/using-string-literals-as-c-template-parameters/

#include <algorithm>

namespace yq {
    template <size_t N>
    struct string_literal {
        constexpr string_literal(const char (&str)[N])
        {
            std::copy_n(str, N, value);
        }
        char value[N];
    };
}
