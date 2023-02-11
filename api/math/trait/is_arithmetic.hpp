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

    template <typename T> struct is_arithmetic : std::is_arithmetic<T> {};
    template <typename T> struct is_arithmetic<std::complex<T>> : public is_arithmetic<T> {};
    template <typename T, typename D>             struct is_arithmetic<MKS<T,D>> : public is_arithmetic<T> {};
    template <typename T, typename D, double K>   struct is_arithmetic<SCALED<T,D,K>> : public is_arithmetic<T> {};
    template <typename T> static constexpr const bool is_arithmetic_v = is_arithmetic<T>::value;
}

