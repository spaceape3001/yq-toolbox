////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/trait/argument_type.hpp>
    
namespace yq {

    template <typename ... Args>
    constexpr argument_types<Args...>     function_argument_types(void(*)(Args...))
    {
        return {};
    }
    
    template <typename T, typename ... Args>
    constexpr argument_types<Args...>     function_argument_types(T(*)(Args...))
    {
        return {};
    }

    template <typename C, typename ... Args>
    constexpr argument_types<Args...>     function_argument_types(void(C::*)(Args...))
    {
        return {};
    }


    template <typename C, typename ... Args>
    constexpr argument_types<Args...>     function_argument_types(void(C::*)(Args...) const)
    {
        return {};
    }

    template <typename T, typename C, typename ... Args>
    constexpr argument_types<Args...>     function_argument_types(T(C::*)(Args...))
    {
        return {};
    }

    template <typename T, typename C, typename ... Args>
    constexpr argument_types<Args...>     function_argument_types(T(C::*)(Args...) const)
    {
        return {};
    }
    
    
   // //////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename... Args>
    constexpr size_t function_argument_count(void(*)(Args...))
    {
        return sizeof...(Args);
    }

    template <typename T, typename... Args>
    constexpr size_t function_argument_count(T(*)(Args...))
    {
        return sizeof...(Args);
    }

    template <typename C, typename... Args>
    constexpr size_t function_argument_count(void(C::*)(Args...))
    {
        return sizeof...(Args);
    }

    template <typename C, typename... Args>
    constexpr size_t function_argument_count(void(C::*)(Args...) const)
    {
        return sizeof...(Args);
    }

    template <typename T, typename C, typename... Args>
    constexpr size_t function_argument_count(T(C::*)(Args...))
    {
        return sizeof...(Args);
    }

    template <typename T, typename C, typename... Args>
    constexpr size_t function_argument_count(T(C::*)(Args...) const)
    {
        return sizeof...(Args);
    }

    // //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    template <typename A, typename... Args>
    constexpr A   function_first_argument(void(*)(A, Args...))
    {
        return A{};
    }
    
    template <typename T, typename A, typename... Args>
    constexpr A   function_first_argument(T(*)(A, Args...))
    {
        return A{};
    }
 
    template <typename C, typename A, typename... Args>
    constexpr A   function_first_argument(void(C::*)(A, Args...))
    {
        return A{};
    }
  
    template <typename C, typename A, typename... Args>
    constexpr A   function_first_argument(void(C::*)(A, Args...) const)
    {
        return A{};
    }
  
    template <typename T, typename C, typename A, typename... Args>
    constexpr A   function_first_argument(T(C::*)(A, Args...))
    {
        return A{};
    }
  
    template <typename T, typename C, typename A, typename... Args>
    constexpr A   function_first_argument(T(C::*)(A, Args...) const)
    {
        return A{};
    }

    // //////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0    
    
    namespace trait_impl {
        template <typename> struct MethodArguments;

        template <typename T, typename C, typename ... Args>
        struct MethodArguments<T(C::*)(Args...)> {
            using args = argument_types<Args...>;
            static constexpr const size_t   count   = sizeof...(Args);
        };
        
        template <typename T, typename C, typename ... Args>
        struct MethodArguments<T(C::*)(Args...) const> {
            using args = argument_types<Args...>;
            static constexpr const size_t   count   = sizeof...(Args);
        };
        
        template <typename C, typename ... Args>
        struct MethodArguments<void (C::*)(Args...)> {
            using args = argument_types<Args...>;
            static constexpr const size_t   count   = sizeof...(Args);
        };
        
        template <typename C, typename ... Args>
        struct MethodArguments<void (C::*)(Args...) const> {
            using args = argument_types<Args...>;
            static constexpr const size_t   count   = sizeof...(Args);
        };

        template <typename T, typename... Args>
        struct MethodArguments<T (*)(Args...)> {
            using args = argument_types<Args...>;
            static constexpr const size_t   count   = sizeof...(Args);
        };
        
        template <typename... Args>
        struct MethodArguments<void (*)(Args...)> {
            using args = argument_types<Args...>;
            static constexpr const size_t   count   = sizeof...(Args);
        };
    }
    
    template <typename T>
    using function_arguments        = trait_impl::MethodArguments<T>::args;
    
    template <size_t N, typename T>
    using function_argument_type_t = trait_impl::argument_type<N, function_arguments<T>>::type;
    
    template <typename T>
    using first_function_argument_type = function_argument_type_t<0,T>;
#endif
}
