////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    /*! \brief Indexing for a binary bucket system
    */
    class BinaryBucket {
    public:
    
        static size_t   parent(size_t n)
        {
            return n >> 1ULL;
        }
        
        static size_t   child_low(size_t n)
        {
            return n << 1ULL;
        }
        
        static size_t   child_high(size_t n)
        {
            return (n << 1ULL) | 1ULL;
        }


        constexpr BinaryBucket() noexcept = default;
        constexpr BinaryBucket(I t) noexcept : m_total(t)  {}

        constexpr I     total() const noexcept { return m_total; }
        
        
    
    private:
        I       m_total = I{};
        
    };
}
