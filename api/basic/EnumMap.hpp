////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Enum.hpp>
#include <basic/Vector.hpp>

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

        static int 	max_key();
        static int 	min_key();
        static bool	valid(E);

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
    int 	EnumMap<E,V>::max_key() 
    {
        static const int 	ret	= E::max_value();
        return ret;
    }

    template <typename E, typename V>
    int 	EnumMap<E,V>::min_key() 
    {
        static const int 	ret	= E::min_value();
        return ret;
    }


    template <typename E, typename V>
    bool	EnumMap<E,V>::valid(E e)
    {
        return E::has_value(e.value());
    }

    template <typename E, typename V>
    V       EnumMap<E,V>::get(E e, V def) const
    {
        if(!valid(e))
            return def;
        return m_values[e.value() - min_key()];
    }

    template <typename E, typename V>
    EnumMap<E,V>::EnumMap(const V& val)
    {
        static const size_t	cnt	= size_t(max_key() - min_key() + 1);
        m_values.resize(cnt, val);
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
        return m_values[e.value() - min_key()];
    }

    template <typename E, typename V>
    const V&	EnumMap<E,V>::operator[](E e) const
    {
        #ifdef _DEBUG
        assert(valid(e));
        #endif
        return m_values[e.value() - min_key()];
    }

}
