////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <math/integer.hpp>

namespace yq {
    template <typename T, size_t N>
    class BitArray {
    public:
    
        static_assert(is_power_two(sizeof(T)), "T must be a power of two in size.");
    
        static constexpr size_t     PER     = sizeof(T) * 8ULL;
        static constexpr size_t     MAX     = PER * N;
        static constexpr size_t     SHIFT   = log_two_approximate(N);
        static constexpr size_t     MASK    = SHIFT - 1;
        
        
        constexpr BitArray()
        {
        }
        
        void    clear()
        {
            for(size_t i=0;i<N;++i)
                m_data[i]   = {};
        }
        
        void    clear(size_t i)
        {
            if(i>=MAX)
                return;

            m_data[index(i)] &= ~mask(i);
        }
        
        constexpr size_t    size() const noexcept { return MAX; }
        
        constexpr bool    operator[](size_t i) const
        {
            if(i>=MAX)
                return false;

            return (m_data[index(i)] & mask(i)) != 0;
        }
        
        void    set(size_t i)
        {
            if(i>=MAX)
                return ;
            m_data[index(i)]  |= mask(i);
        }
        
    private:
        T           m_data[MAX];
        
        static constexpr size_t bit(size_t i) 
        {
            return i % MASK;
        }
        
        static constexpr T      mask(size_t i)
        {
            return T(1) << bit(i);
        }
        
        static constexpr size_t index(size_t i)
        {
            return i >> SHIFT;
        }
        
    };
}

