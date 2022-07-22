////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    template <typename T>
    struct identity_eval : public std::false_type {
    };

    namespace trait {
        template <typename T> static constexpr const bool has_identity_v = identity_eval<T>::value;
    }
    
    template <typename T>
    static constexpr const T identity_v  = identity_eval<T>::make();

    #define IMPL_YQ_IDENTITY(type, ...)                         \
        struct identity_eval<type> : public std::true_type {    \
            static consteval type make()                        \
            {                                                   \
                return __VA_ARGS__;                             \
            }                                                   \
        };
    
    #define YQ_IDENTITY(type, ...)                              \
        template <>                                             \
        IMPL_YQ_IDENTITY(type, __VA_ARGS__)
        
    #define YQ_IDENTITY_1(type, ...)                            \
        template <typename T> requires trait::has_identity_v<T> \
        IMPL_YQ_IDENTITY(type<T>, __VA_ARGS__)
}
