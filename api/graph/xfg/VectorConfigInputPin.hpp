////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/preamble.hpp>

namespace yq::xfg {


    /*! \brief Vector of pins, with config data per pin
    */
    template <typename T, typename C>
    class VectorConfigInputPin {
    public:
        struct Data {
            T   value;
            C   config;
        };
        
        using iterator          = typename std::vector<Data>::iterator;
        using const_iterator    = typename std::vector<Data>::const_iterator;
        using value_type        = T;
        using config_type       = C;
        
        VectorConfigInputPin();
        ~VectorConfigInputPin();
        
        constexpr const_iterator  cbegin() const noexcept;
        constexpr const_iterator  cend() const noexcept;

        constexpr const_iterator  begin() const noexcept;
        constexpr const_iterator  end() const noexcept;
        constexpr iterator        begin() noexcept;
        constexpr iterator        end() noexcept;
        
        bool                empty() const;
        size_t              size() const;
        
        Data&               operator[](size_t);
        const Data&         operator[](size_t) const;
        

    private:
        void            resize(std::span<const C>, const T& v=T{});

        std::vector<Data>   m_data;
    };

    template <typename T, typename C>
    VectorConfigInputPin<T,C>::VectorConfigInputPin()
    {
    }

    template <typename T, typename C>
    VectorConfigInputPin<T,C>::~VectorConfigInputPin()
    {
    }
    
    template <typename T, typename C>
    constexpr typename VectorConfigInputPin<T,C>::const_iterator  VectorConfigInputPin<T,C>::begin() const noexcept
    {
        return m_data.begin();
    }
    
    template <typename T, typename C>
    constexpr typename VectorConfigInputPin<T,C>::iterator        VectorConfigInputPin<T,C>::begin() noexcept
    {
        return m_data.begin();
    }

    template <typename T, typename C>
    constexpr typename VectorConfigInputPin<T,C>::const_iterator  VectorConfigInputPin<T,C>::cbegin() const noexcept
    {
        return m_data.cbegin();
    }
    
    template <typename T, typename C>
    constexpr typename VectorConfigInputPin<T,C>::const_iterator  VectorConfigInputPin<T,C>::cend() const noexcept
    {
        return m_data.cend();
    }

    template <typename T, typename C>
    bool                VectorConfigInputPin<T,C>::empty() const
    {
        return m_data.empty();
    }
    
    template <typename T, typename C>
    constexpr typename VectorConfigInputPin<T,C>::const_iterator  VectorConfigInputPin<T,C>::end() const noexcept
    {
        return m_data.end();
    }
    
    template <typename T, typename C>
    constexpr typename VectorConfigInputPin<T,C>::iterator        VectorConfigInputPin<T,C>::end() noexcept
    {
        return m_data.end();
    }
    
    template <typename T, typename C>
    size_t              VectorConfigInputPin<T,C>::size() const
    {
        return m_data.size();
    }
    
    template <typename T, typename C>
    void                VectorConfigInputPin<T,C>::resize(std::span<const C>cfg, const T& v)
    {
        m_data.resize(cfg.size());
        for(size_t n=0;n<cfg.size();++n){
            m_data[n].config    = cfg.config;
            m_data[n].value     = v;
        }
    }
    
    template <typename T, typename C>
    typename VectorConfigInputPin<T,C>::Data& VectorConfigInputPin<T,C>::operator[](size_t n)
    {
        return m_data[n];
    }
    
    template <typename T, typename C>
    const VectorConfigInputPin<T,C>::Data& VectorConfigInputPin<T,C>::operator[](size_t n) const
    {
        return m_data[n];
    }
    
}

