////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ByteArray.hpp"
#include <yq-toolbox/errors.hpp>

namespace yq {

    ByteArray::ByteArray() = default;
    ByteArray::ByteArray(const ByteArray&) = default;
    ByteArray::ByteArray(ByteArray&&) = default;
    ByteArray::ByteArray(const char*z, size_t cb) : m_data(z, cb) {}
    ByteArray::ByteArray(const Vector<char>&dat) : m_data(dat) {}
    ByteArray::ByteArray(Vector<char>&&dat) : m_data(std::move(dat)) {}
    
    ByteArray::ByteArray(std::initializer_list<uint8_t> d) : m_data((const char*) std::data(d), d.size())
    {
    }
    
    ByteArray&  ByteArray::operator=(const ByteArray&) = default;
    ByteArray&  ByteArray::operator=(ByteArray&&) = default;
    
    ByteArray::~ByteArray() = default;
    
    char&           ByteArray::operator[](size_t n) 
    { 
        return m_data[n]; 
    }

    char            ByteArray::operator[](size_t n) const 
    { 
        return m_data[n]; 
    }
    
    std::error_code ByteArray::append(const char* z, size_t cb)
    {
        static const std::error_code    badAlloc = errors::memory_allocation_failed();
    
        try {
            m_data.append(z, cb);
            return {};
        }
        catch(std::bad_alloc&)
        {
            return badAlloc;
        }
    }

    std::string_view    ByteArray::as_view() const 
    { 
        return std::string_view(m_data.data(), m_data.size()); 
    }
    
    char*           ByteArray::data() 
    { 
        return m_data.data(); 
    }
    
    const char*     ByteArray::data() const 
    { 
        return m_data.data(); 
    }
    
    bool            ByteArray::empty() const 
    { 
        return m_data.empty(); 
    }
    
    std::error_code ByteArray::reserve(size_t z) 
    { 
        static const std::error_code    badAlloc = errors::memory_allocation_failed();
        try {
            m_data.reserve(z); 
            return {};
        }
        catch(std::bad_alloc&)
        {
            return badAlloc;
        }
    }

    std::error_code ByteArray::resize(size_t z)
    {
        static const std::error_code    badAlloc = errors::memory_allocation_failed();
        try {
            m_data.resize(z);
            return {};
        }
        catch(std::bad_alloc&)
        {
            return badAlloc;
        }
    }
    
    std::error_code ByteArray::resize(size_t z, char ch)
    {
        static const std::error_code    badAlloc = errors::memory_allocation_failed();
        try {
            m_data.resize(z, ch);
            return {};
        }
        catch(std::bad_alloc&)
        {
            return badAlloc;
        }
    }

    void            ByteArray::setData(Vector<char>&&dat)
    {
        m_data  = std::move(dat);
    }
    
    size_t          ByteArray::size() const 
    { 
        return m_data.size(); 
    }
    
    ByteArray&  ByteArray::operator<<(char ch)
    {
        m_data.push_back(ch);
        return *this;
    }
    
    bool    ByteArray::operator==(const ByteArray&) const = default;
}

