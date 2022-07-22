////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <array>

namespace yq {
    namespace trait {

        template <typename> struct is_stdarray : std::false_type {};
        template <typename T, std::size_t N>
        struct is_stdarray<std::array<T,N>> : std::true_type {};
        
        template <typename T>
        inline constexpr bool is_stdarray_v = is_stdarray<T>::value;

    }
}
