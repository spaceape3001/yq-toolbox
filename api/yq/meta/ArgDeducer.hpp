////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::args {
    #if 0
    template <class T, class ... A> 
    struct VoidClassArgDeducer {
        static constexpr const unsigned count = sizeof...<A>;
        using class_t       = T;
        using args_t        = A...;
        using result_t      = void;
    };
    #endif
    
    template <class T, class A, bool K> 
    struct VoidSingleClassArgDeducer {
        static constexpr const unsigned count       = 1;
        static constexpr const bool     is_const    = K;
        using class_t       = T;
        using arg_t         = A;
        using result_t      = void;
    };
    
    template <class T, class A, class R, bool K> 
    struct ClassSingleArgDeducer {
        static constexpr const unsigned count = 1;
        static constexpr const bool     is_const    = K;
        using class_t       = T;
        using arg_t         = A;
        using result_t      = R;
    };

    template <class T, class A>
    constexpr VoidClassSingleArgDeducer<T,A,true>   deduce(void (T::*)(const A&) const)
    {
        return {};
    }

    template <class T, class A>
    constexpr VoidClassSingleArgDeducer<T,A,false>  deduce(void (T::*)(const A&))
    {
        return {};
    }
    
    template <class T, class A>
    constexpr VoidClassSingleArgDeducer<T,A,true>   deduce(void (T::*)(A&) const)
    {
        return {};
    }

    template <class T, class A>
    constexpr VoidClassSingleArgDeducer<T,A,false>  deduce(void (T::*)(A&))
    {
        return {};
    }

    template <class T, class A>
    constexpr VoidClassSingleArgDeducer<T,A,true>   deduce(void (T::*)(A) const)
    {
        return {};
    }
    
    template <class T, class A>
    constexpr VoidClassSingleArgDeducer<T,A,false>  deduce(void (T::*)(A))
    {
        return {};
    }
}
