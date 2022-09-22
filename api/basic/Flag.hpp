////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Enum.hpp"
#include <assert.h>

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


    /*! \brief A flag object for enums (up to 64-values)
    
        \tparam E   the enumeration for bit-values
        \tparam T   Data type to represet the bit-field, default 64-bit.
    */
    template <typename E, typename T=uint64_t>
    class Flag {
    public:
        //! Captures the enumeration parameter
        using DefEnum   = E;
        //! Captures the bit-field type parameter
        using DefType   = T;
        //! Pulls out the actual enumeration type to be more friendly to get
        using enum_t    = typename E::enum_t;

        //! Mask for enum value
        static T mask(enum_t e)
        {
            #ifdef _DEBUG
            assert((e>=0) && (e < 8*sizeof(T)) && "Enum value out of range!");
            #endif
            
            return T(1) << e;
        }
        
        //! All flags, set
        static Flag all()
        {
            return Flag(~T(0));
        }
        

        //!  Default constructor, all flags clear ....
        Flag() : m_value(0) {}
        
        //! Constructs by list of enumerated values
        Flag(std::initializer_list<enum_t> flags) : m_value(0)
        {
            for(enum_t e : flags)
                m_value |= mask(e);
        }
        
        //! Constructs with ONE enumerated value
        Flag(enum_t e) : m_value(mask(e)) {}

        //! Constructs by bit-field
        Flag(T v) : m_value(v) {}
        
        //! Constructs by comma separate string
        Flag(std::string_view k, std::string_view sep=",") : 
            m_value(flag_decode<T>(E::staticEnumInfo(), k, sep))
        {
        }
        
        //! Our value
        T       value() const { return m_value; }
        
        //! Returns new flag with specified enumeration set
        Flag        operator+(enum_t e) const
        {
            return Flag(m_value | mask(e));
        }

        //! Returns new flag that has flags of left and flags of right combined
        Flag        operator+(Flag f) const
        {
            return Flag(m_value | f.m_value );
        }
        
        //! Sets specified bit on the left
        Flag&       operator += (enum_t e)
        {
            m_value |= mask(e);
            return *this;
        }

        //! Returns new flag with specified bit not set
        Flag        operator-(enum_t e) const
        {
            return Flag(m_value & ~mask(e));
        }
        
        //! Returns new flag with flags of left but excluding ones on right
        Flag        operator-(Flag f) const
        {
            return Flag(m_value & ~f.m_value);
        }

        //! Unsets specified bit
        Flag&       operator -= (enum_t e)
        {
            m_value &= ~mask(e);
            return *this;
        }
        
        //! Returns new flag, flipping set and clear bits
        //! (ie, bits that were set are now clear, and bits that were clear are now set)
        Flag        operator~() const
        {
            return Flag(~m_value);
        }
        
        //! Union the bits
        Flag       operator |(enum_t e) const
        {
            return Flag(m_value | mask(e));
        }
        
        //! Union the bits
        Flag&      operator |=(enum_t e)
        {
            m_value |= mask(e);
            return *this;
        }

        //! Union the bits
        Flag       operator |(Flag f) const
        {
            return Flag(m_value | f.m_value);
        }

        //! Union the bits
        Flag&      operator |=(Flag f)
        {
            m_value |= f.m_value;
            return *this;
        }

        //! Intersection of bits
        Flag        operator&(enum_t e) const
        {
            return Flag(m_value & mask(e));
        }
        
        //! Intersection of bits
        Flag&      operator &=(enum_t e)
        {
            m_value &= mask(e);
            return *this;
        }

        //! Intersection of bits
        Flag       operator &(Flag f) const
        {
            return Flag(m_value & f.m_value);
        }
     
        //! Intersection of bits
        Flag&      operator &=(Flag f)
        {
            m_value &= f.m_value;
            return *this;
        }

        //! XOR the bits
        Flag        operator^(enum_t e) const
        {
            return Flag(m_value ^ mask(e));
        }
        
        //! XOR the bits
        Flag&      operator ^=(enum_t e)
        {
            m_value ^= mask(e);
            return *this;
        }

        //! XOR the bits
        Flag       operator ^(Flag f) const
        {
            return Flag(m_value ^ f.m_value);
        }

        //! XOR the bits
        Flag&      operator ^=(Flag f)
        {
            m_value ^= f.m_value;
            return *this;
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

        //! TRUE if bit is set
        bool is_set(enum_t e) const
        {
            return (m_value & mask(e))?true:false;
        }
        
        //! TRUE if bit is clear
        bool is_clear(enum_t e) const
        {
            return (m_value & mask(e))?true:false;
        }
        
        //! Tests specified bit, returning true
        bool    operator[](enum_t e) const
        {
            return is_set(e);
        }
        
        //! TRUE if any bit is set
        operator bool() const
        {
            return static_cast<bool>(m_value);
        }
        
        //! Sets specified bit
        void    set(enum_t e)
        {
            m_value |= mask(e);
        }
        
        //! Clears specified bit
        void    clear(enum_t e)
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
