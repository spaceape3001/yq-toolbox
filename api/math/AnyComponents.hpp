////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {

    /*! \brief Holder for "ANY" component
    
        This is meant as a *temporary* holder for a value (ie, by reference) 
        for a vector/tensor type of object so that comparisons can then be done
        such that *any* component that succeds is a pass
    */
    template <typename V>
    struct AnyComponents {
    
        //! Captures the template parameter
        using value_type        = std::remove_cv_t<V>;
    
        //! Capture the value type's component type
        using component_type    = typename value_type::component_type;

        //! Data itself, a reference
        V& value;
        
        //  --------------------------------------------------------------------------------------------------------
        //  LESS THAN
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator<(const V& rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a < b; } );
        }

        constexpr bool    operator<(const AnyComponents& rhs) const noexcept
        {
            return value.any_test(rhs.value, [](component_type a, component_type b) -> bool { return a < b; } );
        }

        constexpr bool    operator<(component_type rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a < b; } );
        }

        friend constexpr bool    operator<(component_type lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b < a; } );
        }

        friend constexpr bool    operator<(const value_type& lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b < a; } );
        }

        //  --------------------------------------------------------------------------------------------------------
        //  LESS THAN OR EQUAL
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator<=(const V& rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a <= b; } );
        }

        constexpr bool    operator<=(const AnyComponents& rhs) const noexcept
        {
            return value.any_test(rhs.value, [](component_type a, component_type b) -> bool { return a <= b; } );
        }

        constexpr bool    operator<=(component_type rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a <= b; } );
        }

        friend constexpr bool    operator<=(component_type lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b <= a; } );
        }

        friend constexpr bool    operator<=(const value_type& lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b <= a; } );
        }

        //  --------------------------------------------------------------------------------------------------------
        //  GREATER
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator>(const V& rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a > b; } );
        }

        constexpr bool    operator>(const AnyComponents& rhs) const noexcept
        {
            return value.any_test(rhs.value, [](component_type a, component_type b) -> bool { return a > b; } );
        }

        constexpr bool    operator>(component_type rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a > b; } );
        }

        friend constexpr bool    operator>(component_type lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b > a; } );
        }

        friend constexpr bool    operator>(const value_type& lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b > a; } );
        }    

        //  --------------------------------------------------------------------------------------------------------
        //  GREATER OR EQUAL
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator>=(const V& rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a >= b; } );
        }

        constexpr bool    operator>=(const AnyComponents& rhs) const noexcept
        {
            return value.any_test(rhs.value, [](component_type a, component_type b) -> bool { return a >= b; } );
        }

        constexpr bool    operator>=(component_type rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a >= b; } );
        }

        friend constexpr bool    operator>=(component_type lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b >= a; } );
        }

        friend constexpr bool    operator>=(const value_type& lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b >= a; } );
        }    

        //  --------------------------------------------------------------------------------------------------------
        //  EQUALITY
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator==(const V& rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a == b; } );
        }

        constexpr bool    operator==(const AnyComponents& rhs) const noexcept
        {
            return value.any_test(rhs.value, [](component_type a, component_type b) -> bool { return a == b; } );
        }

        constexpr bool    operator==(component_type rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a == b; } );
        }

        friend constexpr bool    operator==(component_type lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b == a; } );
        }

        friend constexpr bool    operator==(const value_type& lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b == a; } );
        }

        //  --------------------------------------------------------------------------------------------------------
        //  INEQUALITY
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator!=(const V& rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a != b; } );
        }

        constexpr bool    operator!=(const AnyComponents& rhs) const noexcept
        {
            return value.any_test(rhs.value, [](component_type a, component_type b) -> bool { return a != b; } );
        }

        constexpr bool    operator!=(component_type rhs) const noexcept
        {
            return value.any_test(rhs, [](component_type a, component_type b) -> bool { return a != b; } );
        }

        friend constexpr bool    operator!=(component_type lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b != a; } );
        }

        friend constexpr bool    operator!=(const value_type& lhs, const AnyComponents& rhs) noexcept
        {
            return rhs.value.any_test(lhs, [](component_type a, component_type b) -> bool { return b != a; } );
        }

    };
}
