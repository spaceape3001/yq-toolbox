////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    template <typename> 
    struct return_type : std::false_type { 
        using type  = void;
    };
    
    template <typename R, typename ... Args>
    struct return_type<R(Args...)> : std::true_type {
        using type  = R;
    };
 
    template <typename R, typename C, typename ... Args>
    struct return_type<R(C::*)(Args...)> : std::true_type {
        using type  = R;
    };

    template <typename R, typename C, typename ... Args>
    struct return_type<R(C::*)(Args...) const> : std::true_type {
        using type  = R;
    };
    
    template <typename T> 
    using return_type_t = return_type<T>::type;
    
    template <typename T>
    using return_type_v = return_type<T>::value;
}

