////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <cstdlib>
#include <cmath>

namespace yq {
    template <typename T>
    struct abs_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const bool has_abs_v = abs_eval<T>::value;
    }

    template <typename T>
    requires trait::has_abs_v<T>
    auto abs(const T& v) 
    {
        return abs_eval<T>::compute(v);
    }

    #define IMPL_YQ_ABS(type, ...)                              \
        struct abs_eval<type> : public std::true_type {         \
            static  auto compute(const type& v)                 \
            {                                                   \
                return __VA_ARGS__;                             \
            }                                                   \
        };
    
    #define YQ_ABS(type, ...)                                   \
        template <>                                             \
        IMPL_YQ_ABS(type, __VA_ARGS__)
        
    #define YQ_ABS_1(type, ...)                                 \
        template <typename T> requires trait::has_abs_v<T>      \
        IMPL_YQ_ABS(type<T>, __VA_ARGS__)
        
    template <typename T>
    requires std::is_arithmetic_v<T>
    struct abs_eval<T> : public std::true_type {         
        static  auto compute(T v)        
        {                                                   
            return std::abs(v);
        }                                                   
    };
    
}
