////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>

namespace yq {
    namespace trait {
        template <typename...> struct always_false : std::false_type {};
        template <typename...> static constexpr bool always_false_v    = false;
    }
}
