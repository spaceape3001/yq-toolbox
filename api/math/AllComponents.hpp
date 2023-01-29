////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Holder for "ALL" component
    
        This is meant as a *temporary* holder for a value (ie, by reference) 
        for a vector/tensor type of object so that operations can be done
        to all components.
        
        Started off for testing all components, however, it's evolving to include other element-by-element
        operations.
    */
    template <typename V>
    struct AllComponents {
    
        //! Captures the template parameter
        using value_type        = V;
    
        //! Capture the value type's component type
        using component_type    = typename V::component_type;

        //! Data itself, a reference
        const V& value;
        
        //  --------------------------------------------------------------------------------------------------------
        //  LESS THAN
        //  --------------------------------------------------------------------------------------------------------

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

        friend constexpr bool    operator<(const value_type& lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b < a; } );
        }

        //  --------------------------------------------------------------------------------------------------------
        //  LESS THAN OR EQUAL
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator<=(const V& rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a <= b; } );
        }

        constexpr bool    operator<=(const AllComponents& rhs) const noexcept
        {
            return value.all_test(rhs.value, [](component_type a, component_type b) -> bool { return a <= b; } );
        }

        constexpr bool    operator<=(component_type rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a <= b; } );
        }

        friend constexpr bool    operator<=(component_type lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b <= a; } );
        }

        friend constexpr bool    operator<=(const value_type& lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b <= a; } );
        }

        //  --------------------------------------------------------------------------------------------------------
        //  GREATER
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator>(const V& rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a > b; } );
        }

        constexpr bool    operator>(const AllComponents& rhs) const noexcept
        {
            return value.all_test(rhs.value, [](component_type a, component_type b) -> bool { return a > b; } );
        }

        constexpr bool    operator>(component_type rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a > b; } );
        }

        friend constexpr bool    operator>(component_type lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b > a; } );
        }

        friend constexpr bool    operator>(const value_type& lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b > a; } );
        }    

        //  --------------------------------------------------------------------------------------------------------
        //  GREATER OR EQUAL
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator>=(const V& rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a >= b; } );
        }

        constexpr bool    operator>=(const AllComponents& rhs) const noexcept
        {
            return value.all_test(rhs.value, [](component_type a, component_type b) -> bool { return a >= b; } );
        }

        constexpr bool    operator>=(component_type rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a >= b; } );
        }

        friend constexpr bool    operator>=(component_type lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b >= a; } );
        }

        friend constexpr bool    operator>=(const value_type& lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b >= a; } );
        }    

        //  --------------------------------------------------------------------------------------------------------
        //  EQUALITY
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator==(const V& rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a == b; } );
        }

        constexpr bool    operator==(const AllComponents& rhs) const noexcept
        {
            return value.all_test(rhs.value, [](component_type a, component_type b) -> bool { return a == b; } );
        }

        constexpr bool    operator==(component_type rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a == b; } );
        }

        friend constexpr bool    operator==(component_type lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b == a; } );
        }

        friend constexpr bool    operator==(const value_type& lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b == a; } );
        }

        //  --------------------------------------------------------------------------------------------------------
        //  INEQUALITY
        //  --------------------------------------------------------------------------------------------------------

        constexpr bool    operator!=(const V& rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a != b; } );
        }

        constexpr bool    operator!=(const AllComponents& rhs) const noexcept
        {
            return value.all_test(rhs.value, [](component_type a, component_type b) -> bool { return a != b; } );
        }

        constexpr bool    operator!=(component_type rhs) const noexcept
        {
            return value.all_test(rhs, [](component_type a, component_type b) -> bool { return a != b; } );
        }

        friend constexpr bool    operator!=(component_type lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b != a; } );
        }

        friend constexpr bool    operator!=(const value_type& lhs, const AllComponents& rhs) noexcept
        {
            return rhs.value.all_test(lhs, [](component_type a, component_type b) -> bool { return b != a; } );
        }

        //  --------------------------------------------------------------------------------------------------------
        //  ELEMENT BITS
        //  --------------------------------------------------------------------------------------------------------
        
        constexpr value_type    operator+(component_type rhs) const noexcept
        {
            return value.all_add(rhs);
        }

        constexpr value_type    operator-(component_type rhs) const noexcept
        {
            return value.all_subtract(rhs);
        }
    };
}
