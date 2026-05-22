////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Enum.hpp>
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

        static_assert(std::is_enum_v<E> || is_template_enum_v<E>, "E must be an enumeration type");

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
        if constexpr (std::is_enum_v<E>){
            static const auto& em = enumeration<E>();
            return (ssize_t) em.value(maximum_k())-(ssize_t) em.value(minimum_k())+2;
        }
        
        if constexpr (is_template_enum_v<E>){
            return (size_t)(E::max_value()-E::min_value()+2);
        }
        
        return 2;
    }


    template <typename E, typename V>
    E 	    EnumMap<E,V>::max_key() 
    {
        if constexpr (std::is_enum_v<E>){
            return enumeration<E>().value(maximum_k());
        }
        
        if constexpr (is_template_enum_v<E>){
            static const E 	ret = (typename E::enum_t) E::max_value();
            return ret;
        }
        
        return {};
    }

    template <typename E, typename V>
    E 	EnumMap<E,V>::min_key() 
    {
        if constexpr (std::is_enum_v<E>){
            return enumeration<E>().value(minimum_k());
        }
        
        if constexpr (is_template_enum_v<E>){
            static const E 	ret = (typename E::enum_t) E::min_value();
            return ret;
        }
        
        return {};
    }

    template <typename E, typename V>
    ssize_t  EnumMap<E,V>::index(E e)
    {
        if constexpr (std::is_enum_v<E>){
            return (ssize_t) e - (ssize_t) min_key();
        }
        
        if constexpr (is_template_enum_v<E>){
            return (ssize_t) e.value() - (ssize_t) min_key().value();
        }
        
        return 0;
    }
    
    template <typename E, typename V>
    bool	EnumMap<E,V>::valid(E e)
    {
        if constexpr (std::is_enum_v<E>){
            return enumeration<E>().value(HAS, e);
        }
        
        if constexpr (is_template_enum_v<E>){
            return E::has_value(e);
        }
        
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
