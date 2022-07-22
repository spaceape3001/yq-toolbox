////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>

namespace yq {
    namespace trait {
        template <typename...> struct always_true : std::true_type {};
        template <typename...> static constexpr bool always_true_v    = true;
    }
}
