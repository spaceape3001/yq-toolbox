////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    template <typename T>
    struct zero_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const bool has_zero_v = zero_eval<T>::value;
    }
    
    template <typename T>
    static constexpr const T zero_v  = zero_eval<T>::make();

    #define IMPL_YQ_ZERO(type, ...)                             \
        struct zero_eval<type> : public std::true_type {        \
            static consteval type make()                        \
            {                                                   \
                return __VA_ARGS__;                             \
            }                                                   \
        };
    
    #define YQ_ZERO(type, ...)                                  \
        template <>                                             \
        IMPL_YQ_ZERO(type, __VA_ARGS__)
        
    #define YQ_ZERO_1(type, ...)                                \
        template <typename T> requires trait::has_zero_v<T>     \
        IMPL_YQ_ZERO(type<T>, __VA_ARGS__)

    template <typename T>
    requires std::is_arithmetic_v<T>
    struct zero_eval<T> : public std::true_type {
        static consteval T make()
        {
            return T{0}; 
        }                                                   
    };
}
