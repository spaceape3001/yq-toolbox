////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    template <typename T>
    struct sqrt_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const  bool has_sqrt_v = sqrt_eval<T>::value;
    }

    template <typename T>
    requires trait::has_sqrt_v<T>
    bool sqrt(const T& v) 
    {
        return sqrt_eval<T>::compute(v);
    }

    #define IMPL_YQ_SQRT(type, ...)                             \
        struct sqrt_eval<type> : public std::true_type {        \
            static  auto compute(const type& v)        \
            {                                                   \
                return __VA_ARGS__;                             \
            }                                                   \
        };
    
    #define YQ_SQRT(type, ...)                                  \
        template <>                                             \
        IMPL_YQ_SQRT(type, __VA_ARGS__)
        
    #define YQ_SQRT_1(type, ...)                                \
        template <typename T> requires trait::has_sqrt_v<T>     \
        IMPL_YQ_SQRT(type<T>, __VA_ARGS__)
        
        
    template <typename T>
    requires std::is_floating_point_v<T>
    struct sqrt_eval<T> : public std::true_type { 
        static constexpr auto compute(T v) 
        {
            return std::sqrt(v);
        }
    };
}
