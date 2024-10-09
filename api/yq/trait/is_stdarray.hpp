////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <array>

namespace yq {

    //! Tests to see if type is std::array
    template <typename> struct is_stdarray : std::false_type {};
    template <typename T, std::size_t N>
    struct is_stdarray<std::array<T,N>> : std::true_type {};
    
    //! TRUE if the given T is a std::array
    template <typename T>
    inline constexpr bool is_stdarray_v = is_stdarray<T>::value;

}
