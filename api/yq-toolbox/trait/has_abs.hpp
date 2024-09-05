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

    template <typename T> static constexpr const bool has_abs_v = abs_eval<T>::value;

    template <typename T>
    requires has_abs_v<T>
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
        template <typename T>                                   \
        IMPL_YQ_ABS(type<T>, __VA_ARGS__)
        
    YQ_ABS(uint8_t, v )
    YQ_ABS(uint16_t, v )
    YQ_ABS(uint32_t, v )
    YQ_ABS(uint64_t, v )
    YQ_ABS(double, std::abs(v) )
    YQ_ABS(float, std::abs(v) )
    YQ_ABS(int8_t, std::abs(v) )
    YQ_ABS(int16_t, std::abs(v) )
    YQ_ABS(int32_t, std::abs(v) )
    YQ_ABS(int64_t, std::abs(v) )
}

