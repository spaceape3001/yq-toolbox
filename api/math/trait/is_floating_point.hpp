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
        template <typename T> struct is_floating_point : std::is_floating_point<T> {};
        template <typename T> struct is_floating_point<std::complex<T>> : is_floating_point<T> {};
        template <typename T, typename D>             struct is_floating_point<MKS<T,D>> : is_floating_point<T> {};
        template <typename T, typename D, double K>   struct is_floating_point<SCALED<T,D,K>> : is_floating_point<T> {};
        template <typename T> static constexpr const bool is_floating_point_v = is_floating_point<T>::value;
    }
}

