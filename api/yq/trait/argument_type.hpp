////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <cstddef>

namespace yq {
    template <typename... Args> 
    struct argument_types { 
        using types     = argument_types;  
    };
    
    template <size_t N, typename T>
    struct argument_type;
    
    template <size_t N, typename Head, typename ... Tail>
    struct argument_type<N, argument_types<Head,Tail...>> : argument_type<N-1, argument_types<Tail...>> {};
    
    template <typename Head, typename ... Tail> 
    struct argument_type<0, argument_types<Head,Tail...>> {
        using type = Head;
    };

    template <size_t N, typename...Args>
    using argument_type_t = argument_type<N, argument_types<Args...>>::type;
    
    template <typename ... Args>
    using first_argument_type = argument_type_t<0, Args...>;
}

