////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/Vector.hpp>
#include <string_view>

namespace yq {

    /*! \brief Array of bytes
    */
    class ByteArray {
    public:

        //! Defaulted constructor
        ByteArray() = default;
        
        //! Defaulted copy constructor
        ByteArray(const ByteArray&) = default;
        
        //! Defaulted move constructor
        ByteArray(ByteArray&&) = default;
        
        //! Create with string & size
        ByteArray(const char*z, size_t cb) : m_data(z, cb) {}
        
        //! Create by copy in vector of data
        ByteArray(const Vector<char>&dat) : m_data(dat) {}
        
        //! Create by move in vector of data
        ByteArray(Vector<char>&&dat) : m_data(std::move(dat)) {}
        
        //! Create by a fixed byte array sequence
        ByteArray(std::initializer_list<uint8_t> d) : m_data((const char*) std::data(d), d.size())
        {
        }
        
        //! Defaulted copy operator
        ByteArray&  operator=(const ByteArray&) = default;

        //! Defaulted move operator
        ByteArray&  operator=(ByteArray&&) = default;
        
        //! Defaulted destructor
        ~ByteArray() = default;
        
        //! Get byte (reference)
        char&           operator[](size_t n) 
        { 
            return m_data[n]; 
        }

        //! Get byte
        char            operator[](size_t n) const 
        { 
            return m_data[n]; 
        }
        
        //! Begin iterator
        auto    begin() { return m_data.begin(); }

        //! Begin iterator
        auto    begin() const { return m_data.begin(); }

        //! Begin iterator
        auto    cbegin() const { return m_data.cbegin(); }

        //! End iterator
        auto    end() { return m_data.end(); }

        //! End iterator
        auto    end() const { return m_data.end(); }

        //! End iterator
        auto    cend() { return m_data.cend(); }
        
        //! Begin reverse iterator
        auto    rbegin() { return m_data.begin(); }

        //! Begin reverse iterator
        auto    rbegin() const { return m_data.begin(); }

        //! Begin reverse iterator
        auto    crbegin() const { return m_data.cbegin(); }
        
        //! End reverse iterator
        auto    rend() { return m_data.end(); }

        //! End reverse iterator
        auto    rend() const { return m_data.end(); }

        //! End reverse iterator
        auto    crend() { return m_data.cend(); }

        //! Appends to a byte array
        ByteArray&      append(const char* z, size_t cb)
        {
            m_data.append(z, cb);
            return *this;
        }

        //! Byte array as a string view
        std::string_view    as_view() const 
        { 
            return std::string_view(m_data.data(), m_data.size()); 
        }
        
        //! Pointer to first byte
        char*           data() 
        { 
            return m_data.data(); 
        }
        
        //! Pointer to first byte
        const char*     data() const 
        { 
            return m_data.data(); 
        }
        
        //! Checks for empty buffer
        bool            empty() const 
        { 
            return m_data.empty(); 
        }
        
        //! Reserves capacity
        void            reserve(size_t z) 
        { 
            m_data.reserve(z); 
        }

        //! Resizes the data
        void            resize(size_t z)
        {
            m_data.resize(z);
        }
        
        //! Resizes the data with specified character
        void            resize(size_t z, char ch)
        {
            m_data.resize(z, ch);
        }

        //! Sets the data
        void            setData(Vector<char>&&dat)
        {
            m_data  = std::move(dat);
        }
        
        //! Size of the data
        size_t          size() const 
        { 
            return m_data.size(); 
        }
        
        //! Concatenates byte onto back of byte array
        ByteArray&  operator<<(char ch)
        {
            m_data.push_back(ch);
            return *this;
        }
        
        //! Defaulted comparison operator
        bool    operator==(const ByteArray&) const = default;
        
        
    //private:
        // this is binary data BTW, no interpretation
        Vector<char>        m_data;
    };
}
