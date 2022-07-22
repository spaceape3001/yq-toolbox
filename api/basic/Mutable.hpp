////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Revision.hpp"
#include <type_traits>

namespace yq {
    template <typename T>
    requires (std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>)
    class Mutable : public Revision {
    public:
    
        Mutable(Revision*m=nullptr) : Revision(m) {}
        
        template <typename=void>
        requires std::is_copy_constructible_v<T>
        Mutable(const T&d, Revision*m=nullptr) : 
            Revision(m), m_data(d) {}
        
        template <typename=void>
        requires std::is_move_constructible_v<T>
        Mutable(T&&d, Revision* m=nullptr) : 
            Revision(m), m_data(std::move(d)) 
        {
        }
        
        template <typename=void>
        requires std::is_copy_assignable_v<T>
        Mutable& operator=(const T& d)
        {
            if(&d != &m_data){
                m_data  = d;
                changed();
            }
            return *this;
        }

        template <typename=void>
        requires std::is_move_assignable_v<T>
        Mutable& operator=(T&& d)
        {
            if(&d != &m_data){
                m_data  = std::move(d);
                changed();
            }
            return *this;
        }
        
        operator const T& () const { return m_data; }
        
        const T* operator->() const noexcept { return &m_data; }
        
        /*! \brief Gets edit access to the object
        
            \note This call increments the revision
        */
        T&          edit() 
        {
            changed();
            return m_data;
        }
        
        const T&    get() const
        {
            return m_data;
        }
        
        
    private:
        T           m_data;
    };
}
