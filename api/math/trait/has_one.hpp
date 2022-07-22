////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    template <typename T>
    struct one_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const bool has_one_v = one_eval<T>::value;
    }
    
    template <typename T>
    static constexpr const T one_v  = one_eval<T>::make();

    #define IMPL_YQ_ONE(type, ...)                              \
        struct one_eval<type> : public std::true_type {         \
            static consteval type make()                        \
            {                                                   \
                return __VA_ARGS__;                             \
            }                                                   \
        };
    
    #define YQ_ONE(type, ...)                                   \
        template <>                                             \
        IMPL_YQ_ONE(type, __VA_ARGS__)
        
    #define YQ_ONE_1(type, ...)                                 \
        template <typename T> requires trait::has_one_v<T>      \
        IMPL_YQ_ONE(type<T>, __VA_ARGS__)

    template <typename T>
    requires std::is_arithmetic_v<T>
    struct one_eval<T> : public std::true_type {
        static consteval T make()
        {
            return T{1}; 
        }                                                   
    };

}
