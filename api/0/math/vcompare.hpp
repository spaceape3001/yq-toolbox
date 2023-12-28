////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  The "<<=" and "<<" are poor ways of doing what I want....

///
//  really, something more like
//      all( a << b ) 
//      any( b >> 6 )
//      any( c == 0 )

//      all(a) <= b;
//      any(a) <= b;
//      a <= all(b)
//      a == any(b)
//
//  where a, b, & c are vectors/tensors, would be ideal
//  
//  Not sure how to capture that... w/o breaking identities on ==

namespace yq {

    template <typename V>
    struct AllComponents {
        using component_type    = typename V::component_type;
    
        const V& value;
        
        constexpr bool    operator<(const V& rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a < b; } );
        }

        constexpr bool    operator<(const AllComponents& rhs) const noexcept
        {
            return value.all_test(rhs.value, [](component_type a, component_type b) -> bool { return a < b; } );
        }

        constexpr bool    operator<(component_type rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a < b; } );
        }

        friend constexpr bool    operator<(component_type lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b < a; } );
        }

        friend constexpr bool    operator<(const V& lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b < a; } );
        }
    };


    template <typename V>
    AllComponents<V>  all(const V& val)
    {
        return { val };
    }

#if 0    
    // old ideas
    template <typename AllExpr>
    bool   any(const AllExpr& expr);
    

    template <typename ... Args> bool all(Args... args);
    template <typename ... Args> bool any(Args... args);
#endif
}
