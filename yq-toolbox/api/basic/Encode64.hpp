////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>
#include <cstdint>

namespace yq {

    class ByteArray;
    
    class Encode64 {
    public:

        struct E64 {
            uint8_t     a, b, c, d;
            
            bool operator==(const E64&) const = default;
        };
        
        struct R64 {
            uint8_t     a, b, c;

            bool operator==(const R64&) const = default;
        };

        static E64 encode64(R64);
        static R64 decode64(E64);
    
        /*! \brief Minimum size for output
        
            This returns the likely number of bytes required for the given input size.
        */
        size_t          decode_size(size_t) const;
        
        size_t          encode_size(size_t) const;
        
        /*! \brief Encodes data
        */
        size_t          encode(const void*, size_t, char*, size_t)  const;

        /*! \brief Decodes data 
        
            This decodes the given input characters into a sequence of uint8 numbers.
            \param[in]  text        Pointer to input text
            \param[in]  text_size   Number of characters to text
            \param[out] output      Pointer to output buffer
            \param[out] output_size Number of characters available
            \return Number of bytes placed into output
        */
        size_t          decode(const char*, size_t, uint8_t*, size_t)  const;

        Encode64(const char*, char);
        
    private:
        uint8_t         m_decode[256];
        char            m_encode[64];
        char            m_pad;
        
        uint8_t         c2e(char) const;
        char            e2c(uint8_t) const;
    };
    
    const Encode64&     base64();
    
    
    ByteArray           base64_decode(std::string_view);
    size_t              base64_decode_size(size_t);
    std::string         base64_encode(const void*, size_t);
    std::string         base64_encode(const ByteArray&);
    std::string         base64_encode(std::initializer_list<uint8_t>);
    size_t              base64_encode_size(size_t);
}

