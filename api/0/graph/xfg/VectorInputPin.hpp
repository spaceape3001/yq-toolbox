////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/preamble.hpp>
#include <vector>

namespace yq::xfg {
    template <typename T>
    class VectorInputPin {
    public:
        
        using iterator          = typename std::vector<T>::iterator;
        using const_iterator    = typename std::vector<T>::const_iterator;
        using value_type        = T;
        
        VectorInputPin();
        ~VectorInputPin();
        
        constexpr const_iterator  cbegin() const noexcept;
        constexpr const_iterator  cend() const noexcept;

        constexpr const_iterator  begin() const noexcept;
        constexpr const_iterator  end() const noexcept;
        constexpr iterator        begin() noexcept;
        constexpr iterator        end() noexcept;
        
        bool                empty() const;
        size_t              size() const;
        
        T&                  operator[](size_t);
        const T&            operator[](size_t) const;

    private:
        void                resize(size_t, const T& v=T{});

        std::vector<T>  m_data;
    };

    template <typename T>
    VectorInputPin<T>::VectorInputPin()
    {
    }

    template <typename T>
    VectorInputPin<T>::~VectorInputPin()
    {
    }

    template <typename T>
    constexpr typename VectorInputPin<T>::const_iterator  VectorInputPin<T>::cbegin() const noexcept
    {
        return m_data.cbegin();
    }

    template <typename T>
    constexpr typename VectorInputPin<T>::const_iterator  VectorInputPin<T>::cend() const noexcept
    {
        return m_data.end();
    }

    template <typename T>
    constexpr typename VectorInputPin<T>::const_iterator  VectorInputPin<T>::begin() const noexcept
    {
        return m_data.begin();
    }

    template <typename T>
    constexpr typename VectorInputPin<T>::const_iterator  VectorInputPin<T>::end() const noexcept
    {
        return m_data.end();
    }
    

    template <typename T>
    constexpr typename VectorInputPin<T>::iterator        VectorInputPin<T>::begin() noexcept
    {
        return m_data.begin();
    }
    

    template <typename T>
    constexpr typename VectorInputPin<T>::iterator        VectorInputPin<T>::end() noexcept
    {
        return m_data.end();
    }
    
    
    template <typename T>
    bool                VectorInputPin<T>::empty() const
    {
        return m_data.empty();
    }

    template <typename T>
    size_t              VectorInputPin<T>::size() const
    {
        return m_data.size();
    }

    template <typename T>
    void                VectorInputPin<T>::resize(size_t sz, const T& v)
    {
        m_data.resize(sz, v);
    }
    
    template <typename T>
    T&                  VectorInputPin<T>::operator[](size_t sz)
    {
        return m_data[sz];
    }

    template <typename T>
    const T&            VectorInputPin<T>::operator[](size_t sz) const
    {
        return m_data[sz];
    }
}

