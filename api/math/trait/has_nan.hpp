////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <limits>
#include <basic/preamble.hpp>
#include <cmath>

namespace yq {

    template <typename T>
    struct nan_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const bool has_nan_v = nan_eval<T>::value;
    }
    
    template <typename T>
    static constexpr const T nan_v  = nan_eval<T>::make();

    #define IMPL_YQ_NAN(type, ...)                              \
        struct nan_eval<type> : public std::true_type {         \
            static consteval type make()                        \
            {                                                   \
                return __VA_ARGS__;                             \
            }                                                   \
        };
    
    #define YQ_NAN(type, ...)                                   \
        template <>                                             \
        IMPL_YQ_NAN(type, __VA_ARGS__)
        
    #define YQ_NAN_1(type, ...)                                 \
        template <typename T> requires trait::has_nan_v<T>      \
        IMPL_YQ_NAN(type<T>, __VA_ARGS__)
        
    #define YQ_IS_NAN_1(type, ...)                              \
        template <typename T>                                   \
        requires trait::has_nan_v<T>                            \
        bool is_nan(const type<T>& v)                           \
        {                                                       \
            return __VA_ARGS__;                                 \
        }

    template <typename T>
    requires std::is_floating_point_v<T>
    struct nan_eval<T> : public std::true_type {
        static consteval T make()
        {
            return std::numeric_limits<T>::quiet_NaN();                             
        }                                                   
    };

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr bool  is_nan(T v)
    {
        return std::isnan(v);
    }
}

