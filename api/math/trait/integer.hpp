////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <type_traits>
#include <cstdint>

namespace yq {

    template <typename T> struct integer : public std::false_type {};
    
    template <typename T> static constexpr const bool has_integer_v = integer<T>::value;
    template <typename T> using integer_t = typename integer<T>::type;
    template <typename T> static constexpr const bool is_integer_v = std::is_same_v<T,integer_t<T>>;
    
    #define YQ_INTEGER(theType) template <> struct integer<theType> : public std::true_type { using type = theType; };
    
    YQ_INTEGER(int8_t)
    YQ_INTEGER(int16_t)
    YQ_INTEGER(int32_t)
    YQ_INTEGER(int64_t)

    YQ_INTEGER(uint8_t)
    YQ_INTEGER(uint16_t)
    YQ_INTEGER(uint32_t)
    YQ_INTEGER(uint64_t)
    
    #define YQ_INTEGER_1(theType) template<typename T> struct integer<theType<T>> : public integer<T> {};
}

