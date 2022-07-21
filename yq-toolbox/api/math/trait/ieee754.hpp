////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>

namespace yq {
    template <typename T> struct ieee754 : public std::false_type {};
    
    template <typename T> static constexpr const bool has_ieee754_v = ieee754<T>::value;
    template <typename T> using ieee754_t = typename ieee754<T>::type;
    template <typename T> static constexpr const bool is_ieee754_v = std::is_same_v<T,ieee754_t<T>>;
    
    #define YQ_IEEE754(theType) template <> struct ieee754<theType> : public std::true_type { using type = theType; };
    
    YQ_IEEE754(double)
    YQ_IEEE754(float)
    
    #define YQ_IEEE754_1(theType) template<typename T> struct ieee754<theType<T>> : public ieee754<T> {};
}

