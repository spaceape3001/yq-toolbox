////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/HttpStatus.hpp>

namespace yq {

    class Curl {
    public:
        Curl();
        ~Curl();
        
        
        std::string         get_effective_url() const;
        
        void                set_url(const Url&);
        void                set_url(const UrlView&);
        void                set_url(const std::string&);
        void                set_url(const char*);
        
        //using JsonResult    = std::pair<json,HttpStatus>;
        //using UInt8Result   = std::pair<Vector<uint8_t>,HttpStatus>;
        //using BytesResult   = std::pair<ByteArray,HttpStatus>;
        
        HttpStatus          exec();
        
        const Vector<uint8_t>&      rx() const { return m_rx; }
        ByteArray                   rx_bytes() const;
        json                        rx_json() const;
        
    private:
        Curl(const Curl&) = delete;
        Curl(Curl&&) = delete;
        Curl& operator=(const Curl&) = delete;
        Curl& operator=(Curl&&) = delete;
        
        void*               m_curl;
        Vector<uint8_t>     m_rx;
        
        static size_t   rx_bytes_impl(char*, size_t, size_t, Curl*);
        
    };
}
