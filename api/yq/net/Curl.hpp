////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/net/HttpStatus.hpp>
#include <yq/container/Vector.hpp>
#include <yq/typedef/json.hpp>
#include <yq/typedef/url.hpp>

namespace yq {
    class ByteArray;

	/*! Simple C++ Curl wrapper
	*/
    class Curl {
    public:
    
		//! Default constructor (creates the curl connection)
        Curl();
        
        #if 0
        // disabled until I can syntax check this
        explicit Curl(const Url&);
        explicit Curl(const UrlView&);
        explicit Curl(const std::string&);
        explicit Curl(const char*);
        #endif

        //! Destructor (destroys the curl connection)
        ~Curl();
        
        //! Returns the effective URL of our connection
        std::string         get_effective_url() const;
        
        //! Set the target URL (call *BEFORE* exec())
        void                set_url(const Url&);
        void                set_url(const UrlView&);
        void                set_url(const std::string&);
        void                set_url(const char*);
        
        //using JsonResult    = std::pair<json,HttpStatus>;
        //using UInt8Result   = std::pair<Vector<uint8_t>,HttpStatus>;
        //using BytesResult   = std::pair<ByteArray,HttpStatus>;
        
        HttpStatus          exec();
        
        const Vector<uint8_t>&  rx() const { return m_rx; }
        ByteArray               rx_bytes() const;
        json                    rx_json() const;
        
    private:
        Curl(const Curl&) = delete;
        Curl(Curl&&) = delete;
        Curl& operator=(const Curl&) = delete;
        Curl& operator=(Curl&&) = delete;
        
        void*                   m_curl;
        Vector<uint8_t>     m_rx;
        
        static size_t   rx_bytes_impl(char*, size_t, size_t, Curl*);
        
    };
}
