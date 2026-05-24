////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Enumeration.hpp>
#include <yq/container/Vector.hpp>

#include <cassert>

namespace yq {

    /*! \brief Enum-based Map
     * 
     * 	This provides an enum-based lookup vector, so it's O(1) access.  
     * Iteration support to be provided at a later date (maybe).
     * 
     * \note WARNING: This will create an entry for 
     * 	EACH/EVERY value between min/max, so be careful!!
     */
    template <typename E, typename V>
    class EnumMap {
    public:

        static_assert(std::is_enum_v<E>, "E must be an enumeration type");

        static E 	    max_key();
        static E 	    min_key();
        static bool	    valid(E);
        static ssize_t  index(E);
        static size_t   count();
        

        EnumMap(const V& val={});	// auto-creates the vector
        ~EnumMap();

        V           get(E, V def={}) const;
        V&			operator[](E);
        const V&	operator[](E) const;
    private:
        Vector<V>	m_values;
    };

            //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //      IMPLEMENTATION
            //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename E, typename V>
    size_t   EnumMap<E,V>::count()
    {
        static const auto& em = enumeration<E>();
        return (ssize_t) em.value(maximum_k())-(ssize_t) em.value(minimum_k())+2;
    }


    template <typename E, typename V>
    E 	    EnumMap<E,V>::max_key() 
    {
        return enumeration<E>().value(maximum_k());
    }

    template <typename E, typename V>
    E 	EnumMap<E,V>::min_key() 
    {
        return enumeration<E>().value(minimum_k());
    }

    template <typename E, typename V>
    ssize_t  EnumMap<E,V>::index(E e)
    {
        return (ssize_t) e - (ssize_t) min_key();
    }
    
    template <typename E, typename V>
    bool	EnumMap<E,V>::valid(E e)
    {
        return enumeration<E>().value(HAS, e);
        
        return false;
    }

    /////////////////////////////////////////////

    template <typename E, typename V>
    EnumMap<E,V>::EnumMap(const V& val)
    {
        m_values.resize(count(), val);
    }

    template <typename E, typename V>
    EnumMap<E,V>::~EnumMap()
    {
    }

    template <typename E, typename V>
    V&			EnumMap<E,V>::operator[](E e)
    {
        #ifdef _DEBUG
        assert(valid(e));
        #endif
        
        ssize_t n   = index(e);
        if(n<0 || n>=(ssize_t) count())
            n   = count();
        return m_values[n];
    }

    template <typename E, typename V>
    const V&	EnumMap<E,V>::operator[](E e) const
    {
        #ifdef _DEBUG
        assert(valid(e));
        #endif

        ssize_t n   = index(e);
        if(n<0 || n>= (ssize_t) count())
            n   = count();
        return m_values[n];
    }

    template <typename E, typename V>
    V       EnumMap<E,V>::get(E e, V def) const
    {
        ssize_t n   = index(e);
        if(n<0 || n>=(ssize_t) count()-1)
            return def;
        return m_values[n];
    }


}
