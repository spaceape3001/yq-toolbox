////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>

namespace yq {
    template <typename T, typename DIM>             struct MKS;
    template <typename T, typename DIM, double K>   struct SCALED;

    template <typename T> struct ieee754s : public std::false_type {};
    
    template <typename T> static constexpr const bool has_ieee754_v = ieee754s<T>::value;
    template <typename T> using ieee754_t = typename ieee754s<T>::type;
    template <typename T> static constexpr const bool is_ieee754_v = std::is_same_v<T,ieee754s<T>>;
    
    #define YQ_IEEE754(theType) template <> struct ieee754s<theType> : public std::true_type { using type = theType; };
    
    YQ_IEEE754(double)
    YQ_IEEE754(float)
    
    #define YQ_IEEE754_1(theType) template<typename T> struct ieee754s<theType<T>> : public ieee754s<T> {};

    template<typename T, typename DIM> 
    struct ieee754s<MKS<T,DIM>> : public ieee754s<T> {
    };

    template<typename T, typename DIM,double K> 
    struct ieee754s<SCALED<T,DIM,K>> : public ieee754s<T> {
    };
    
    constexpr double ieee754(double v) 
    { 
        return v; 
    }

    constexpr float ieee754(float v) 
    { 
        return v; 
    }
}

