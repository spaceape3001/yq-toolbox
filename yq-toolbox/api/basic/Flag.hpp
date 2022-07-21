////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Enum.hpp"
#include <assert.h>

namespace yq {

    std::string     flag_string(const EnumDef* def, uint64_t values, std::string_view sep=",");
    template <typename T>
    T               flag_decode(const EnumDef* def, std::string_view keys, std::string_view sep=",");


    /*! \brief A flag object for enums (up to 64-values)
    */
    template <typename E, typename T=uint64_t>
    class Flag {
    public:
        using DefEnum   = E;
        using DefType   = T;
        using enum_t    = typename E::enum_t;

        static T mask(enum_t e)
        {
            #ifdef _DEBUG
            assert((e>=0) && (e < 8*sizeof(T)) && "Enum value out of range!");
            #endif
            
            return T(1) << e;
        }
        
        static Flag all()
        {
            return Flag(~T(0));
        }
        

        //  Default ....
        Flag() : m_value(0) {}
        
        Flag(std::initializer_list<enum_t> flags) : m_value(0)
        {
            for(enum_t e : flags)
                m_value |= mask(e);
        }
        
        Flag(enum_t e) : m_value(mask(e)) {}

        Flag(T v) : m_value(v) {}
        
        Flag(std::string_view k, std::string_view sep=",") : 
            m_value(flag_decode<T>(E::staticEnumInfo(), k, sep))
        {
        }
        
        T       value() const { return m_value; }
        
        Flag        operator+(enum_t e) const
        {
            return Flag(m_value | mask(e));
        }

        Flag        operator+(Flag f) const
        {
            return Flag(m_value | f.m_value );
        }
        
        Flag&       operator += (enum_t e)
        {
            m_value |= mask(e);
            return *this;
        }

        Flag        operator-(enum_t e) const
        {
            return Flag(m_value & ~mask(e));
        }
        
        Flag        operator-(Flag f) const
        {
            return Flag(m_value & ~f.m_value);
        }

        Flag&       operator -= (enum_t e)
        {
            m_value &= ~mask(e);
            return *this;
        }
        
        Flag        operator~() const
        {
            return Flag(~m_value);
        }
        
        Flag       operator |(enum_t e) const
        {
            return Flag(m_value | mask(e));
        }
        
        Flag&      operator |=(enum_t e)
        {
            m_value |= mask(e);
            return *this;
        }

        Flag       operator |(Flag f) const
        {
            return Flag(m_value | f.m_value);
        }

        Flag&      operator |=(Flag f)
        {
            m_value |= f.m_value;
            return *this;
        }

        Flag        operator&(enum_t e) const
        {
            return Flag(m_value & mask(e));
        }
        
        Flag&      operator &=(enum_t e)
        {
            m_value &= mask(e);
            return *this;
        }

        Flag       operator &(Flag f) const
        {
            return Flag(m_value & f.m_value);
        }
     
        Flag&      operator &=(Flag f)
        {
            m_value &= f.m_value;
            return *this;
        }

        Flag        operator^(enum_t e) const
        {
            return Flag(m_value ^ mask(e));
        }
        
        Flag&      operator ^=(enum_t e)
        {
            m_value ^= mask(e);
            return *this;
        }

        Flag       operator ^(Flag f) const
        {
            return Flag(m_value ^ f.m_value);
        }

        Flag&      operator ^=(Flag f)
        {
            m_value ^= f.m_value;
            return *this;
        }
        
        bool    operator==(const Flag& b) const
        {
            return m_value == b.m_value;
        }

        bool    operator!=(const Flag& b) const
        {
            return m_value != b.m_value;
        }

        bool is_set(enum_t e) const
        {
            return (m_value & mask(e))?true:false;
        }
        
        bool is_clear(enum_t e) const
        {
            return (m_value & mask(e))?true:false;
        }
        
        bool    operator[](enum_t e) const
        {
            return is_set(e);
        }
        
        operator bool() const
        {
            return static_cast<bool>(m_value);
        }
        
        
        void    set(enum_t e)
        {
            m_value |= mask(e);
        }
        
        void    clear(enum_t e)
        {
            m_value &= ~mask(e);
        }

        std::string as_string(std::string_view sep=",") const
        {
            return flag_string(E::staticEnumInfo(), m_value, sep);
        }

    private:
        T    m_value;
    };

    template <typename E>
    Flag<E>     all_set()
    {
        return Flag<E>::all();
    }

}
