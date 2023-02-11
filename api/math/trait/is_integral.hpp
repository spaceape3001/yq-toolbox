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

    //! Detecting whether something is integer based (vs floating point) based
    template <typename T> struct is_integer : std::is_integral<T> {};
    template <typename T> struct is_integer<std::complex<T>> : is_integer<T> {};
    template <typename T> static constexpr const bool is_integer_v = is_integer<T>::value;

    #define YQ_IS_INTEGER_1(theType) template<typename T> struct is_integer<theType<T>> : public is_integer<T> {};
    
    template <typename T, typename DIM>
    struct is_integer<MKS<T,DIM>> : public is_integer<T> {
    };

    template <typename T, typename DIM, double K>
    struct is_integer<SCALED<T,DIM,K>> : public is_integer<T> {
    };
}

