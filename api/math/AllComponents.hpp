////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Holder for "ANY" component
    
        This is meant as a *temporary* holder for a value (ie, by reference) 
        for a vector/tensor type of object so that comparisons can then be done
        such that *all* component that succeds is a pass
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
    };
}
