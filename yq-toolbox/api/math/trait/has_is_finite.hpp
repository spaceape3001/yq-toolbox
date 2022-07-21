////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <cmath>

namespace yq {
    template <typename T>
    struct is_finite_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const bool has_is_finite_v = is_finite_eval<T>::value;
    }
    
    template <typename T>
    requires trait::has_is_finite_v<T>
    bool is_finite(const T& v) 
    {
        return is_finite_eval<T>::compute(v);
    }

    #define IMPL_YQ_IS_FINITE(type, ...)                            \
        struct is_finite_eval<type> : public std::true_type {       \
            static constexpr auto compute(const type& v)            \
            {                                                       \
                return __VA_ARGS__;                                 \
            }                                                       \
        };
    
    #define YQ_IS_FINITE(type, ...)                                 \
        template <>                                                 \
        IMPL_YQ_IS_FINITE(type, __VA_ARGS__)
        
    #define YQ_IS_FINITE_1(type, ...)                               \
        template <typename T> requires trait::has_is_finite_v<T>    \
        IMPL_YQ_IS_FINITE(type<T>, __VA_ARGS__)
        
    template <typename T>
    requires std::is_floating_point_v<T>
    struct is_finite_eval<T> : public std::true_type { 
        static constexpr auto compute(T v) 
        {
            return std::isfinite(v);
        }
    };
}
