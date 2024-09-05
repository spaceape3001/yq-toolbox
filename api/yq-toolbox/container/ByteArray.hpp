////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq-toolbox/container/Vector.hpp>
#include <string_view>
#include <system_error>

namespace yq {

    /*! \brief Array of bytes
    */
    class ByteArray {
    public:

        //! Default constructor
        ByteArray();
        
        //! Copy constructor
        ByteArray(const ByteArray&);
        
        //! Move constructor
        ByteArray(ByteArray&&);
        
        //! Create with string & size
        ByteArray(const char*z, size_t cb);
        
        //! Create by copy in vector of data
        ByteArray(const Vector<char>&dat);
        
        //! Create by move in vector of data
        ByteArray(Vector<char>&&dat);
        
        //! Create by a fixed byte array sequence
        ByteArray(std::initializer_list<uint8_t> d);
        
        //! Copy operator
        ByteArray&  operator=(const ByteArray&);

        //! Move operator
        ByteArray&  operator=(ByteArray&&);
        
        //! Destructor
        ~ByteArray();
        
        //! Get byte (reference)
        char&           operator[](size_t n);

        //! Get byte
        char            operator[](size_t n) const;
        
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
        std::error_code  append(const char* z, size_t cb);

        //! Byte array as a string view
        std::string_view    as_view() const;
        
        //! Pointer to first byte
        char*           data();
        
        //! Pointer to first byte
        const char*     data() const;
        
        //! Checks for empty buffer
        bool            empty() const;
        
        //! Reserves capacity
        std::error_code reserve(size_t z);

        //! Resizes the data
        std::error_code resize(size_t z);
        
        //! Resizes the data with specified character
        std::error_code resize(size_t z, char ch);

        //! Sets the data
        void            setData(Vector<char>&&dat);
        
        //! Size of the data
        size_t          size() const;
        
        //! Concatenates byte onto back of byte array
        ByteArray&  operator<<(char ch);
        
        //! Defaulted comparison operator
        bool    operator==(const ByteArray&) const;
        
        
    //private:
        // this is binary data BTW, no interpretation
        Vector<char>        m_data;
    };
}
