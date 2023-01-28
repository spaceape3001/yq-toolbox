////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    namespace trait {
        template <typename T> struct is_arithmetic : std::is_arithmetic<T> {};
        template <typename T> static constexpr const bool is_arithmetic_v = is_arithmetic<T>::value;
    }
}

