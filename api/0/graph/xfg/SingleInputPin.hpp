////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/preamble.hpp>

namespace yq::xfg {
    template <typename T>         
    class SingleInputPin {
    public:
        using iterator          = T*;
        using const_iterator    = const T*;
        using value_type        = T;
        
        constexpr SingleInputPin() noexcept = default;
        constexpr SingleInputPin(const T& _d) noexcept : m_data(_d) {}
        
        constexpr auto      operator<=>(const SingleInputPin& p) const noexcept = default;
        
        constexpr const T*  cbegin() const noexcept;
        constexpr const T*  cend() const noexcept;

        constexpr const T*  begin() const noexcept;
        constexpr const T*  end() const noexcept;
        constexpr T*        begin() noexcept;
        constexpr T*        end() noexcept;
        
        bool                empty() const;
        size_t              size() const;
        
        constexpr const T&  operator*() const noexcept;
        constexpr T&        operator*()  noexcept;
        constexpr const T*  operator->() const noexcept;
        constexpr T*        operator->()  noexcept;
        
        T&                  operator[](size_t);
        const T&            operator[](size_t) const;
        
    private:
        T       m_data = {};
    };


    template <typename T>         
    constexpr const T&  SingleInputPin<T>::operator*() const noexcept 
    { 
        return m_data; 
    }

    template <typename T>         
    constexpr T&        SingleInputPin<T>::operator*()  noexcept 
    { 
        return m_data; 
    }

    template <typename T>         
    constexpr const T*  SingleInputPin<T>::operator->() const noexcept 
    { 
        return &m_data; 
    }

    template <typename T>         
    constexpr T*        SingleInputPin<T>::operator->()  noexcept 
    { 
        return &m_data; 
    }
    
    template <typename T>         
    T&                  SingleInputPin<T>::operator[](size_t)
    {
        return m_data;
    }

    template <typename T>         
    const T&            SingleInputPin<T>::operator[](size_t) const
    {
        return m_data;
    }

    template <typename T>         
    constexpr T*        SingleInputPin<T>::begin() noexcept 
    { 
        return &m_data; 
    }


    template <typename T>         
    constexpr const T*  SingleInputPin<T>::begin() const noexcept 
    { 
        return &m_data; 
    }


    template <typename T>         
    constexpr const T*  SingleInputPin<T>::cbegin() const noexcept 
    { 
        return &m_data; 
    }

    template <typename T>         
    constexpr const T*  SingleInputPin<T>::cend() const noexcept 
    { 
        return 1 + &m_data; 
    }

    template <typename T>         
    bool                SingleInputPin<T>::empty() const 
    { 
        return false; 
    }

    template <typename T>         
    constexpr T*        SingleInputPin<T>::end() noexcept 
    { 
        return 1 + &m_data; 
    }
    
    template <typename T>         
    constexpr const T*  SingleInputPin<T>::end() const noexcept 
    { 
        return 1 + &m_data; 
    }

    template <typename T>         
    size_t              SingleInputPin<T>::size() const 
    { 
        return 1; 
    }
    
}

