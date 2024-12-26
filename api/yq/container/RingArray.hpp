////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <initializer_list>
#include <span>
#include <yq/keywords.hpp>

namespace yq {


    /*! \brief Fixed Ring Buffer
    
        This implements a fixed-ring type of buffer; for once
        full, it'll overwrite old data.  
        
        Indexing... will be in terms of age.  index(0) will 
        correspond to the zero entered item (note, invalid in 
        an EMPTY array).
        
        There will be two 'halves' to the data, above/below 
        the pivot point index.  "LOW" will be the data that's
        for low indexes, HIGH will be for higher indexes.  
        For unfull arrays, and for one spot in the full-fill 
        rotation, the high size will be zero.  Low will always
        be non-zero unless empty
    */
    template <typename T, size_t N>
    class RingArray {
    public:
    
        static_assert(N>=2);    // pointless if 0..1
        static constexpr const size_t   K7          = N + N;
        static constexpr const size_t   CAPACITY    = N;
    
        RingArray(){}
        
        RingArray(std::span<const T> values)
        {
            for(const T& v : values)
                push(v);
        }
        
        RingArray(std::initializer_list<const T> values)
        {
            for(const T& v : values)
                push(v);
        }

        RingArray(const RingArray&) = default;
        RingArray& operator=(const RingArray&) = default;

        ~RingArray(){}

        T&          at(size_t n)
        {
            return m_data[index(n)];
        }
        
        const T&    at(size_t n) const
        {
            return m_data[index(n)];
        }

        T&          operator[](size_t n)
        {
            return m_data[index(n)];
        }
        
        const T&    operator[](size_t n) const
        {
            return m_data[index(n)];
        }

        //! Our capacity (FIXED)
        constexpr size_t capacity() const noexcept
        { 
            return N; 
        }
        
        void    clear()
        {
            m_zero          = K7;
        }
        
        //! Tests for empty buffer
        bool empty() const
        {
            return m_zero >= K7;
        }
        
        /*! \brief Checks for equivalency
        
            Two ring arrays are considered the same if the data within
            them matches, in order.  Note, their zero "pivot" point
            might be different.
        */
        bool    equivalent(const RingArray& rhs) const
        {
            size_t  m   = size();
            if(m != rhs.size())
                return false;
            for(size_t n = 0; n<m; ++n){
                if(value(n) != rhs.value(n))
                    return false;
            }
            return true;
        }
        
        //! TRUE if we're full (overwriting will occur)
        bool full() const
        {
            return m_zero <= N;
        }
        
        //! Our "zero" value (used for testing)
        size_t zero() const { return m_zero; }
        
        //! Adds a value
        void  push(const T&v)
        {
            m_data[advance()] = v;
        }
        
        void  push(T&&v)
        {
            m_data[advance()] = std::move(v);
        }
        
        RingArray&      operator<<(const T&v)
        {
            push(v);
            return *this;
        }
        
        RingArray&      operator<<(T&&v)
        {
            push(std::move(v));
            return *this;
        }

        //! Number of valid entries
        size_t size() const noexcept
        {
            return (m_zero < N) ? N : (K7-m_zero);
        }
        
        //! Number of low-index entries
        size_t size(low_k) const noexcept
        {
            return (m_zero < N) ? (N-m_zero) : (K7-m_zero);
        }
        
        //! Number of high-index entries
        size_t size(high_k) const
        {
            return (m_zero && (m_zero < N)) ? ( m_zero - 1 ) : 0;
        }
        
        //! Span to lowside data
        std::span<const T>  span(low_k) const
        {
            return std::span<const T>(m_data + m_zero, m_data + N);
        }
        
        //! Span to highside data
        std::span<const T>  span(high_k) const
        {
            if(m_zero < N){
                return std::span<const T>(m_data, m_data + m_zero);
            } else {
                return {};
            }
        }
        
        //! Span to ALL the data (note, might not be in order)
        std::span<const T>  span(all_k) const
        {
            if(m_zero < N)
                return std::span<const T>(m_data, N);
            return std::span<const T>(m_data + m_zero - N, m_data + N);
        }

        operator std::span<const T>() const
        {
            return span(ALL);
        }

        const T&    value(size_t n) const
        {
            return m_data[index(n)];
        }
        
        bool    operator==(const RingArray& rhs) const
        {
            return span(ALL) == rhs.span(ALL);
        }
    
    private:
    
        T       m_data[N];
        size_t  m_zero  = K7;
        
        size_t  index(size_t n) const
        {
            return (m_zero + n) % N;
        }
        
        size_t  advance()
        {
            size_t  m;
            if(!m_zero){            // underflow, reset
                m  = m_zero    = N-1;
            } else if(m_zero <= N){  // full, nab
                m  = --m_zero;
            } else {                // not yet full
                m  = --m_zero - N;
            }
            return m;
        }
    };
}
