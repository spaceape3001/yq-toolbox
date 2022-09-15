////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <string_view>

namespace yq {

    /*! \brief Buffer with fixed data
        
        Buffer with fixed-data (ie, in the class)
        
        \tparam N   Number of bytes
        
        It'll have a size of the buffer, and a useful "count" that lets the caller
        fill it in progressively.
    */
    //  TODO -- rename, SIZE -> CAPACITY, and count -> size....
    template <size_t N>
    class BasicBuffer {
    public:
        //! Capture template parameter, maximum size of the buffer
        static constexpr const size_t  CAPACITY    = N;
    
        //! Size of the buffer
        static consteval size_t capacity() { return N; }
        
        //! Advances the count of the buffer
        void                advance(size_t n)
        {
            m_size = std::min(m_size+n, N);
        }
        
        //!  Appends to the buffer, up to its capacity
        void                append(const char*z, size_t cnt)
        {
            if(!z || !cnt)
                return ;
            if(m_size >= N)
                return ;
                
            cnt     = std::min(N-m_size, cnt);
            memcpy(m_buffer+m_size, z, cnt);
            m_size += cnt;
        }

        //! Appends to the buffer, up to its capacity
        void                append(std::string_view sv)
        {
            advance(sv.data(), sv.size());
        }
        
        //! Buffer as a string view
        std::string_view    as_view() const
        {
            return std::string_view(m_buffer, m_size);
        }
        
        //! Buffer as a string view starting at N
        std::string_view    as_view(size_t n)
        {
            if(n>=m_size)
                n   = m_size;
            return std::string_view(m_buffer+n, m_size-n);
        }
        
        //! Number of free bytes available
        size_t              available() const { return N - m_size; }
        
        //! "Clears" the buffer down to size of zero
        void                clear()
        {
            m_size      = 0;
        }
        
        //! Start of data
        char*               data() { return m_buffer; }

        //! Start of data
        const char*         data() const { return m_buffer; }

        //! TRUE if empty
        bool                empty() const { return !m_size; }
        
        //! TRUE if full
        bool                full() const { return m_size >= N; }

        //! Pointer to start of free space
        char*               freespace()  { return m_buffer + m_size; }

        //! Number of bytes so far
        size_t              size() const { return m_size; }
        
        //! Sets the count
        void                size(size_t n)
        {
            m_size = std::min(n, N);
        }
        
        //! Sets the buffer
        template <typename T>
        BasicBuffer&        operator=(const T& data)
        {
            static_assert(sizeof(T) <= N);
            memcpy(m_buffer, &data, sizeof(T));
            m_size = sizeof(T);
            return *this;
        }
        
    protected:
        size_t  m_size       = 0;
        char    m_buffer[N];
    };
}
