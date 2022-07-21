////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/Vector.hpp>
#include <string_view>

namespace yq {
    class ByteArray {
    public:

        ByteArray() = default;
        ByteArray(const ByteArray&) = default;
        ByteArray(ByteArray&&) = default;
        
        ByteArray(const char*z, size_t cb) : m_data(z, cb) {}
        ByteArray(const Vector<char>&dat) : m_data(dat) {}
        ByteArray(Vector<char>&&dat) : m_data(std::move(dat)) {}
        
        ByteArray(std::initializer_list<uint8_t> d) : m_data((const char*) std::data(d), d.size())
        {
        }
        
        ByteArray&  operator=(const ByteArray&) = default;
        ByteArray&  operator=(ByteArray&&) = default;
        
        ~ByteArray() = default;
        
        
        char&           operator[](size_t n) 
        { 
            return m_data[n]; 
        }

        char            operator[](size_t n) const 
        { 
            return m_data[n]; 
        }
        
        auto    begin() { return m_data.begin(); }
        auto    begin() const { return m_data.begin(); }
        auto    cbegin() const { return m_data.cbegin(); }
        auto    end() { return m_data.end(); }
        auto    end() const { return m_data.end(); }
        auto    cend() { return m_data.cend(); }
        
        auto    rbegin() { return m_data.begin(); }
        auto    rbegin() const { return m_data.begin(); }
        auto    crbegin() const { return m_data.cbegin(); }
        
        auto    rend() { return m_data.end(); }
        auto    rend() const { return m_data.end(); }
        auto    crend() { return m_data.cend(); }

        ByteArray&      append(const char* z, size_t cb)
        {
            m_data.append(z, cb);
            return *this;
        }

        std::string_view    as_view() const 
        { 
            return std::string_view(m_data.data(), m_data.size()); 
        }
        
        char*           data() 
        { 
            return m_data.data(); 
        }
        
        const char*     data() const 
        { 
            return m_data.data(); 
        }
        
        bool            empty() const 
        { 
            return m_data.empty(); 
        }
        

        void            reserve(size_t z) 
        { 
            m_data.reserve(z); 
        }

        
        void            resize(size_t z)
        {
            m_data.resize(z);
        }
        
        
        void            resize(size_t z, char ch)
        {
            m_data.resize(z, ch);
        }

        void            setData(Vector<char>&&dat)
        {
            m_data  = std::move(dat);
        }
        
        size_t          size() const 
        { 
            return m_data.size(); 
        }
        
        ByteArray&  operator<<(char ch)
        {
            m_data += ch;
            return *this;
        }
        
        bool    operator==(const ByteArray&) const = default;
        
        
    //private:
        // this is binary data BTW, no interpretation
        Vector<char>        m_data;
    };
}
