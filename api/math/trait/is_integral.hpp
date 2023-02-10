////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace std {
    template <typename> class complex;
}

namespace yq {
    template <typename T, typename DIM>             struct MKS;
    template <typename T, typename DIM, double K>   struct SCALED;

    namespace trait {
        template <typename T> struct is_integral : std::is_integral<T> {};
        template <typename T> struct is_integral<std::complex<T>> : is_integral<T> {};
        template <typename T, typename D>             struct is_integral<MKS<T,D>> : is_integral<T> {};
        template <typename T, typename D, double K>   struct is_integral<SCALED<T,D,K>> : is_integral<T> {};
        template <typename T> static constexpr const bool is_integral_v = is_integral<T>::value;
        template <typename T> static constexpr const bool is_integer_v = is_integral<T>::value;
    }
}

