////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/basic/Enum.hpp>
#include <cassert>

namespace yq {

    /*! Creates a separated flag string 
    
        This is what the Flag class defers to, creating a string from a uint64_t bit-field of the values.
    
        \param[in] def      Enumeration definition
        \param[in] values   Bit field of the values
        \param[in] sep      Separator value (default comma)
        \return The string, with each key spearated by the separator
    */
    std::string     flag_string(const EnumDef* def, uint64_t values, std::string_view sep=",");
    
    template <typename T>
    T               flag_decode(const EnumDef* def, std::string_view keys, std::string_view sep=",");

    template <typename T> concept Enumerable = requires {
        typename T::enum_t;
    };


    /*! \brief A flag object for enums (up to 64-values)
    
        \tparam E   the enumeration for bit-values
        \tparam T   Data type to represet the bit-field, default 64-bit.
    */
    template <typename E, typename T=uint64_t>
    class Flag {
    public:
    
        static_assert( is_template_enum_v<E>, "Use Flags instead for non-yq-Enum enumerations (sorry, it's a C++ syntax issue :( )");
    
        //! Captures the enumeration parameter
        using DefEnum   = E;
        //! Captures the bit-field type parameter
        using DefType   = T;
        
        //! Pulls out the actual enumeration type to be more friendly to get
        using enum_t    = typename E::enum_t;

        static constexpr T  mask(E e) noexcept
        {
            return T(1) << T(e.value());
        }
        
        static constexpr T mask(typename E::enum_t e) noexcept 
        {
            return T(1) << T(e);
        }

        
        //! All flags, set
        static consteval Flag all()
        {
            return Flag(ALL,true);
        }
        
        //!  Default constructor, all flags clear ....
        constexpr Flag() noexcept : m_value(0) {}
        
        constexpr Flag(all_t, bool v) noexcept : m_value(v?~T(0):T(0)) {}
        constexpr Flag(all_t) noexcept : Flag(ALL, true) {}
        
        //! Constructs by bit-field
        constexpr Flag(T v) noexcept : m_value(v) {}

        //! Constructs with ONE enumerated value
        constexpr Flag(E e) noexcept : m_value(mask(e)) {}
        
        //! Constructs with ONE enumerated value
        constexpr Flag(typename E::enum_t e) noexcept : m_value(mask(e)) {}
        
        //! Constructs by list of enumerated values
        constexpr Flag(std::initializer_list<E> flags) noexcept : m_value(0)
        {
            for(E e : flags)
                m_value |= mask(e);
        }
        
        //! Constructs by list of enumerated values
        constexpr Flag(std::initializer_list<typename E::enum_t> flags) noexcept : m_value(0)
        {
            for(E e : flags)
                m_value |= mask(e);
        }
        
        
        //! Constructs by comma separate string
        Flag(std::string_view k, std::string_view sep=",") : 
            m_value(flag_decode<T>(E::staticEnumInfo(), k, sep))
        {
        }
        
        //! Our value
        constexpr T value() const noexcept { return m_value; }
        
        //! Sets specified bit
        void    set(E e)
        {
            m_value |= mask(e);
        }
        
        //! Clears specified bit
        void    clear(E e)
        {
            m_value &= ~mask(e);
        }

        /*! Formats to string
            
            \param[in] sep  Separator to use (default comma)
        */
        std::string as_string(std::string_view sep=",") const
        {
            return flag_string(E::staticEnumInfo(), m_value, sep);
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
        

        constexpr Flag      operator~() const noexcept
        { 
            return Flag(~m_value);
        }
        
        //! TRUE if any bit is set
        operator bool() const
        {
            return static_cast<bool>(m_value);
        }
        
        //! Equality operator
        bool    operator==(const Flag& b) const
        {
            return m_value == b.m_value;
        }

        //! Inequality operator
        bool    operator!=(const Flag& b) const
        {
            return m_value != b.m_value;
        }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Flag/Flag
    
        constexpr Flag        operator+(Flag f) const noexcept
        {
            return Flag(m_value | f.m_value );
        }

        constexpr Flag        operator-(Flag f) const noexcept
        {
            return Flag(m_value & ~f.m_value );
        }
        
        constexpr Flag        operator|(Flag f) const noexcept
        {
            return Flag(m_value | f.m_value );
        }
    
        constexpr Flag        operator&(Flag f) const noexcept
        {
            return Flag(m_value & f.m_value );
        }
    
        constexpr Flag        operator^(Flag f) const noexcept
        {
            return Flag(m_value ^ f.m_value );
        }

        
        Flag&   operator+=(Flag f) noexcept
        {
            m_value |= f.m_value;
            return *this;
        }
        
        Flag&   operator-=(Flag f) noexcept
        {
            m_value &= ~f.m_value;
            return *this;
        }
        
        Flag&   operator|=(Flag f) noexcept
        {
            m_value |= f.m_value;
            return *this;
        }
        
        Flag&   operator&=(Flag f) noexcept
        {
            m_value &= f.m_value;
            return *this;
        }

        Flag&   operator^=(Flag f) noexcept
        {
            m_value ^= f.m_value;
            return *this;
        }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Flag/Enum
    
        constexpr Flag        operator+(E e) const noexcept
        {
            return Flag(m_value | mask(e) );
        }
    
        constexpr Flag        operator-(E e) const noexcept
        {
            return Flag(m_value & ~mask(e) );
        }

        constexpr Flag        operator|(E e) const noexcept
        {
            return Flag(m_value | mask(e) );
        }

        constexpr Flag        operator&(E e) const noexcept
        {
            return Flag(m_value & mask(e) );
        }

        constexpr Flag        operator^(E e) const noexcept
        {
            return Flag(m_value ^ mask(e) );
        }

        Flag&   operator+=(E e) noexcept
        {
            m_value |= mask(e);
            return *this;
        }
        
        Flag&   operator-=(E e) noexcept
        {
            m_value &= ~mask(e);
            return *this;
        }
        
        Flag&   operator|=(E e) noexcept
        {
            m_value |= mask(e);
            return *this;
        }
        
        Flag&   operator&=(E e) noexcept
        {
            m_value &= mask(e);
            return *this;
        }

        Flag&   operator^=(E e) noexcept
        {
            m_value ^= mask(e);
            return *this;
        }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Flag/enum_t

        constexpr Flag        operator+(typename E::enum_t e) const noexcept
        {
            return Flag(m_value | mask(e) );
        }
    
        constexpr Flag        operator-(typename E::enum_t e) const noexcept
        {
            return Flag(m_value & ~mask(e) );
        }

        constexpr Flag        operator|(typename E::enum_t e) const noexcept
        {
            return Flag(m_value | mask(e) );
        }

        constexpr Flag        operator&(typename E::enum_t e) const noexcept
        {
            return Flag(m_value & mask(e) );
        }

        constexpr Flag        operator^(typename E::enum_t e) const noexcept
        {
            return Flag(m_value ^ mask(e) );
        }

        Flag&   operator+=(typename E::enum_t e) noexcept
        {
            m_value |= mask(e);
            return *this;
        }
        
        Flag&   operator-=(typename E::enum_t e) noexcept
        {
            m_value &= ~mask(e);
            return *this;
        }
        
        Flag&   operator|=(typename E::enum_t e) noexcept
        {
            m_value |= mask(e);
            return *this;
        }
        
        Flag&   operator&=(typename E::enum_t e) noexcept
        {
            m_value &= mask(e);
            return *this;
        }

        Flag&   operator^=(typename E::enum_t e) noexcept
        {
            m_value ^= mask(e);
            return *this;
        }
        
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Enum/Flag

        friend constexpr Flag        operator+(E e, Flag f) noexcept
        {
            return Flag(mask(e) | f.m_value);
        }

        friend constexpr Flag        operator-(E e, Flag f) noexcept
        {
            return Flag(mask(e) &~ f.m_value);
        }

        friend constexpr Flag        operator|(E e, Flag f) noexcept
        {
            return Flag(mask(e) | f.m_value);
        }

        friend constexpr Flag        operator&(E e, Flag f) noexcept
        {
            return Flag(mask(e) & f.m_value);
        }
        
        friend constexpr Flag        operator^(E e, Flag f) noexcept
        {
            return Flag(mask(e) ^ f.m_value);
        }

    private:
        T    m_value;
    };

    //! Helper for all set of specified enume
    template <typename E>
    Flag<E>     all_set()
    {
        return Flag<E>::all();
    }

}
