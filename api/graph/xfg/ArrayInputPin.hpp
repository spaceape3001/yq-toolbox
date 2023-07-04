////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/preamble.hpp>
#include <array>

namespace yq::xfg {
    template <typename T, size_t N>
    class ArrayInputPin {
    public:
        
        using iterator          = typename std::array<T,N>::iterator;
        using const_iterator    = typename std::array<T,N>::const_iterator;
        using value_type        = T;
        
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
        std::array<T,N>     m_data;
    };

    template <typename T, size_t N>
    constexpr typename ArrayInputPin<T,N>::const_iterator  ArrayInputPin<T,N>::cbegin() const noexcept
    {
        return m_data.cbegin();
    }

    template <typename T, size_t N>
    constexpr typename ArrayInputPin<T,N>::const_iterator  ArrayInputPin<T,N>::cend() const noexcept
    {
        return m_data.end();
    }

    template <typename T, size_t N>
    constexpr typename ArrayInputPin<T,N>::const_iterator  ArrayInputPin<T,N>::begin() const noexcept
    {
        return m_data.begin();
    }

    template <typename T, size_t N>
    constexpr typename ArrayInputPin<T,N>::const_iterator  ArrayInputPin<T,N>::end() const noexcept
    {
        return m_data.end();
    }
    

    template <typename T, size_t N>
    constexpr typename ArrayInputPin<T,N>::iterator        ArrayInputPin<T,N>::begin() noexcept
    {
        return m_data.begin();
    }
    

    template <typename T, size_t N>
    constexpr typename ArrayInputPin<T,N>::iterator        ArrayInputPin<T,N>::end() noexcept
    {
        return m_data.end();
    }
    
    
    template <typename T, size_t N>
    bool                ArrayInputPin<T,N>::empty() const
    {
        return m_data.empty();
    }

    template <typename T, size_t N>
    size_t              ArrayInputPin<T,N>::size() const
    {
        return m_data.size();
    }
    
    template <typename T, size_t N>
    T&                  ArrayInputPin<T,N>::operator[](size_t sz)
    {
        return m_data[sz];
    }

    template <typename T, size_t N>
    const T&            ArrayInputPin<T,N>::operator[](size_t sz) const
    {
        return m_data[sz];
    }
}

