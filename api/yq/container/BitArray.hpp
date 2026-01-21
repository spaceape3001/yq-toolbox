////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <yq/math/integer.hpp>

namespace yq {

    /*! Array of bits
    
        This is an array of bits, consisting of T[N] data,   Thus, the resulting 
        array can contain 8*sizeof(T)*N bits.  (See MAX, below)
    
        \tparam T   integer type
        \tparam N   count of integers to use
    */
    template <typename T, size_t N>
    class BitArray {
    public:
    
        static_assert(is_power_two(sizeof(T)), "T must be a power of two in size.");
        
        #ifdef MAX
        #undef MAX
        #endif
    
        //! Bits per T
        static constexpr size_t     PER     = sizeof(T) * 8ULL;
        
        //! Total number of bits
        static constexpr size_t     MAX     = PER * N;
        
        //! Amount that needs to be shifted to split the index (array entry vs bit)
        static constexpr size_t     SHIFT   = log_two_approximate(PER);
        
        //! Mask needed to split the bit address off the index
        static constexpr size_t     MASK    = (1ULL << SHIFT) - 1;
        
        //! Default constructor
        constexpr BitArray()
        {
        }
        
        //! Clear the bitarray
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
        
        constexpr bool    operator()(size_t i) const
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
        
        void    set(size_t i, bool v)
        {
            if(i>=MAX)
                return ;
            if(v){
                m_data[index(i)]  |= mask(i);
            } else {
                m_data[index(i)] &= ~mask(i);
            }
        }

    private:
        T           m_data[N] = {};
        
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

