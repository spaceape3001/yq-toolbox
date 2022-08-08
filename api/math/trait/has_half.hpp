////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    template <typename T>
    struct half_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const bool has_half_v = half_eval<T>::value;
    }
    
    template <typename T>
    static constexpr const T half_v  = half_eval<T>::make();

    #define IMPL_YQ_HALF(type, ...)                             \
        struct half_eval<type> : public std::true_type {        \
            static consteval type make()                        \
            {                                                   \
                return __VA_ARGS__;                             \
            }                                                   \
        };
    
    #define YQ_HALF(type, ...)                                  \
        template <>                                             \
        IMPL_YQ_HALF(type, __VA_ARGS__)
        
    #define YQ_HALF_1(type, ...)                                \
        template <typename T> requires trait::has_half_v<T>     \
        IMPL_YQ_HALF(type<T>, __VA_ARGS__)

    template <typename T>
    requires std::is_floating_point_v<T>
    struct half_eval<T> : public std::true_type {
        static consteval T make()
        {
            return T{0.5}; 
        }                                                   
    };
}
