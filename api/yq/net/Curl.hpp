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

		//! Creates & sets the url to a CURL connection (note, does not execute)
        explicit Curl(const Url&);

		//! Creates & sets the url to a CURL connection (note, does not execute)
        explicit Curl(const UrlView&);

		//! Creates & sets the url to a CURL connection (note, does not execute)
        explicit Curl(const std::string&);

		//! Creates & sets the url to a CURL connection (note, does not execute)
        explicit Curl(const char*);

        //! Destructor (destroys the curl connection)
        ~Curl();
        
        //! Returns the effective URL of our connection
        std::string         get_effective_url() const;
        
        //! Set the target URL (call *BEFORE* exec())
        void                set_url(const Url&);

        //! Set the target URL (call *BEFORE* exec())
        void                set_url(const UrlView&);

        //! Set the target URL (call *BEFORE* exec())
        void                set_url(const std::string&);

        //! Set the target URL (call *BEFORE* exec())
        void                set_url(const char*);
        
        //using JsonResult    = std::pair<json,HttpStatus>;
        //using UInt8Result   = std::pair<Vector<uint8_t>,HttpStatus>;
        //using BytesResult   = std::pair<ByteArray,HttpStatus>;
        
        //! Executes the connection & query, captures any reply
        HttpStatus          exec();
        
        //! Contents of the received data buffer (after execution)
        const Vector<uint8_t>&  rx() const { return m_rx; }
        
        //! Contents of the received data buffer as a byte array
        //! \note This will be a COPY of the data, so hopefully it's not too much
        ByteArray               rx_bytes() const;
        
        //! Contents of the received data buffer as a json object
        //! \note This will, of course, be a COPY of the data, so hopefully it's not too much
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
