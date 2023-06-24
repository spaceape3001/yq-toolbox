////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>
#include <basic/keywords.hpp>
#include <initializer_list>

namespace yq {


    /*! \brief A flag object for enums (up to 64-values)
    
        \note Unfortunately couldn't get the regular Flag object to work nicely
            with this... no amount of SFINAE requires would get around the
            fact that typename E::enum_t wasn't valid for a straight enum-class.
            Therefore, we had to split.
    
        \tparam E   the enumeration for bit-values
        \tparam T   Data type to represet the bit-field, default 64-bit.
    */
    template <typename E, typename T=uint64_t>
    class Flags {
    public:
    
        //! Captures the enumeration parameter
        using DefEnum   = E;
        //! Captures the bit-field type parameter
        using DefType   = T;
        

        static constexpr T  mask(E e) noexcept
        {
            return T(1) << T(e);
        }
        
        
        //! All flags, set
        static consteval Flags all()
        {
            return Flags(ALL,true);
        }
        
        //!  Default constructor, all flags clear ....
        constexpr Flags() noexcept : m_value(0) {}
        
        constexpr Flags(all_t, bool v) noexcept : m_value(v?~T(0):T(0)) {}
        
        constexpr Flags(all_t) noexcept : Flags(ALL, true) {}

        //! Constructs by bit-field
        constexpr Flags(T v) noexcept : m_value(v) {}

        //! Constructs with ONE enumerated value
        constexpr Flags(E e) noexcept : m_value(mask(e)) {}
        
        //! Constructs by list of enumerated values
        constexpr Flags(std::initializer_list<E> flags) noexcept : m_value(0)
        {
            for(E e : flags)
                m_value |= mask(e);
        }
        
        
        //! Our value
        constexpr T value() const noexcept { return m_value; }
        
        //! Sets specified bit
        void    set(E e)
        {
            m_value |= mask(e);
        }
        
        //! Sets specified bit
        void    set(E e, bool f)
        {
            if(f){
                set(e);
            } else {
                clear(e);
            }
        }

        //! Clears specified bit
        void    clear(E e)
        {
            m_value &= ~mask(e);
        }

        //! TRUE if bit is set
        bool is_set(E e) const
        {
            return (m_value & mask(e))?true:false;
        }
        
        //! TRUE if bit is clear
        bool is_clear(E e) const
        {
            return (m_value & mask(e))?true:false;
        }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  OPERATORS

        //! Tests specified bit, returning true
        bool    operator[](E e) const
        {
            return is_set(e);
        }
        
        bool    operator()(E e) const
        {
            return is_set(e);
        }
        

        constexpr Flags      operator~() const noexcept
        { 
            return Flags(~m_value);
        }
        
        //! TRUE if any bit is set
        operator bool() const
        {
            return static_cast<bool>(m_value);
        }
        
        //! Equality operator
        bool    operator==(const Flags& b) const
        {
            return m_value == b.m_value;
        }

        //! Inequality operator
        bool    operator!=(const Flags& b) const
        {
            return m_value != b.m_value;
        }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Flags/Flags
    
        constexpr Flags        operator+(Flags f) const noexcept
        {
            return Flags(m_value | f.m_value );
        }

        constexpr Flags        operator-(Flags f) const noexcept
        {
            return Flags(m_value & ~f.m_value );
        }
        
        constexpr Flags        operator|(Flags f) const noexcept
        {
            return Flags(m_value | f.m_value );
        }
    
        constexpr Flags        operator&(Flags f) const noexcept
        {
            return Flags(m_value & f.m_value );
        }
    
        constexpr Flags        operator^(Flags f) const noexcept
        {
            return Flags(m_value ^ f.m_value );
        }

        
        Flags&   operator+=(Flags f) noexcept
        {
            m_value |= f.m_value;
            return *this;
        }
        
        Flags&   operator-=(Flags f) noexcept
        {
            m_value &= ~f.m_value;
            return *this;
        }
        
        Flags&   operator|=(Flags f) noexcept
        {
            m_value |= f.m_value;
            return *this;
        }
        
        Flags&   operator&=(Flags f) noexcept
        {
            m_value &= f.m_value;
            return *this;
        }

        Flags&   operator^=(Flags f) noexcept
        {
            m_value ^= f.m_value;
            return *this;
        }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Flags/Enum
    
        constexpr Flags        operator+(E e) const noexcept
        {
            return Flags(m_value | mask(e) );
        }
    
        constexpr Flags        operator-(E e) const noexcept
        {
            return Flags(m_value & ~mask(e) );
        }

        constexpr Flags        operator|(E e) const noexcept
        {
            return Flags(m_value | mask(e) );
        }

        constexpr Flags        operator&(E e) const noexcept
        {
            return Flags(m_value & mask(e) );
        }

        constexpr Flags        operator^(E e) const noexcept
        {
            return Flags(m_value ^ mask(e) );
        }

        Flags&   operator+=(E e) noexcept
        {
            m_value |= mask(e);
            return *this;
        }
        
        Flags&   operator-=(E e) noexcept
        {
            m_value &= ~mask(e);
            return *this;
        }
        
        Flags&   operator|=(E e) noexcept
        {
            m_value |= mask(e);
            return *this;
        }
        
        Flags&   operator&=(E e) noexcept
        {
            m_value &= mask(e);
            return *this;
        }

        Flags&   operator^=(E e) noexcept
        {
            m_value ^= mask(e);
            return *this;
        }
        
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Enum/Flags

        friend constexpr Flags        operator+(E e, Flags f) noexcept
        {
            return Flags(mask(e) | f.m_value);
        }

        friend constexpr Flags        operator-(E e, Flags f) noexcept
        {
            return Flags(mask(e) &~ f.m_value);
        }

        friend constexpr Flags        operator|(E e, Flags f) noexcept
        {
            return Flags(mask(e) | f.m_value);
        }

        friend constexpr Flags        operator&(E e, Flags f) noexcept
        {
            return Flags(mask(e) & f.m_value);
        }
        
        friend constexpr Flags        operator^(E e, Flags f) noexcept
        {
            return Flags(mask(e) ^ f.m_value);
        }

    private:
        T    m_value;
    };

}
