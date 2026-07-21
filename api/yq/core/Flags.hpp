////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstddef>
#include <cstdint>
#include <yq/keywords.hpp>
#include <initializer_list>
#include <string_view>
#include <type_traits>

namespace yq {

    using default_flags_type_t  = uint64_t;

    /*! \brief A flag object for enums (up to 64-values)
    
        \note Unfortunately couldn't get the regular Flag object to work nicely
            with this... no amount of SFINAE requires would get around the
            fact that typename E::enum_t wasn't valid for a straight enum-class.
            Therefore, we had to split.
    
        \tparam E   the enumeration for bit-values
        \tparam T   Data type to represet the bit-field, default 64-bit.
    */
    template <typename E, typename T=default_flags_type_t>
    class Flags {
    public:
    
        struct Checker;
    
        //! Captures the enumeration parameter
        using DefEnum   = E;
        //! Captures the bit-field type parameter
        using DefType   = T;
        using value_type    = T;

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
        
        /*! Constructs all flags to clear/set depending on the parameter
			\param[in] v 	Value to set (on vs off)
        */
        constexpr Flags(all_k, bool v) noexcept : m_value(v?~T(0):T(0)) {}
        
        //! Constructs all flags to be set
        constexpr Flags(all_k) noexcept : Flags(ALL, true) {}

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
        
        /*! Construct from parsing string
        
			This creates a flags object by parsing & interpretting the string.
			
			\param[in] bitString	text to parse
			\param[in] sep 			separator between keys
			\param[out] ok			pass a pointer to a bool to get yes/no on 
									parsing result
        */
        explicit Flags(std::string_view bitString, char sep=',', bool *ok=nullptr);
        std::string as_string(char sep=',') const;
        std::string as_display(char sep=',') const;
        
        
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

        void    set(Flags f)
        {
            m_value |= f.m_value;
        }

        //! Clears specified bit
        void    clear(E e)
        {
            m_value &= ~mask(e);
        }

        void    clear(Flags f)
        {
            m_value &= ~f.m_value;
        }

        void    toggle(E e)
        {
            m_value ^= mask(e);
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
        
        //! TRUE if any are set
        bool any(Flags f) const noexcept
        {
            return (f.m_value & m_value) != T{};
        }

        //! TRUE if all are set
        bool all(Flags f) const noexcept
        {
            return (f.m_value & m_value) == f.m_value;
        }
        
        //! TRUE if none are set
        bool none(Flags f) const noexcept
        {
            return (f.m_value & m_value) == T{};
        }
        
        size_t count() const 
        {
            size_t  cnt = 0;
            for(T n = m_value; n; n >>= 1){
                if(n & 1)
                    ++cnt;
            }
            return cnt;
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
        constexpr bool    operator==(const Flags& b) const noexcept
        {
            return m_value == b.m_value;
        }

        //! Inequality operator
        constexpr bool    operator!=(const Flags& b) const noexcept
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
    

    template <typename E, typename T>
    struct Flags<E,T>::Checker {
        Flags     value, mask;
        
        constexpr Checker(){}
        constexpr Checker(Flags v) : value(v), mask(v) {}
        constexpr Checker(Flags v, Flags m) : value(v), mask(m|v) {}
        
        constexpr bool operator()(Flags v) const
        {
            return (v&mask) == value;
        }
    };
}
