////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Curl.hpp"
#include <yq/container/ByteArray.hpp>
#include <yq/net/json.hpp>
#include <yq/net/Url.hpp>
#include <curl/curl.h>
//#include <0/io/preamble.hpp>

namespace yq {

    size_t   Curl::rx_bytes_impl(char* p, size_t, size_t sz, Curl* c)
    {
        if(p && sz && c)
            c -> m_rx.append((const uint8_t*) p, sz);
        return sz;
    }

    Curl::Curl()
    {
        m_curl  = curl_easy_init();
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Curl::rx_bytes_impl);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
    }

	#if 0
		// disabled until I can syntax check this
	Curl::Curl(const Url&u) : Curl()
	{
		set_url(u);
	}
	
	Curl::Curl(const UrlView&u) : Curl()
	{
		set_url(u);
	}
	
	Curl::Curl(const std::string&u) : Curl()
	{
		set_url(u);
	}
	
	Curl::Curl(const char*u) : Curl()
	{
		set_url(u);
	}
	#endif

    Curl::~Curl()
    {
        curl_easy_cleanup(m_curl);
    }

    HttpStatus          Curl::exec()
    {
        m_rx.clear();
        if(curl_easy_perform(m_curl) == CURLE_OK){
            long    v = 0;
            curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &v);
            return HttpStatus( (HttpStatus::enum_t) v);
        } else
            return HttpStatus::CurlError;
    }


    std::string              Curl::get_effective_url() const
    {
        char*   c;
        if(curl_easy_getinfo(m_curl, CURLINFO_EFFECTIVE_URL, &c) == CURLE_OK)
            return std::string(c);
        return std::string();
    }


    ByteArray           Curl::rx_bytes() const
    {
        return ByteArray((const char*) m_rx.data(), m_rx.size());
    }

    json                Curl::rx_json() const
    {
        if(m_rx.empty())
            return json();
            
        return nlohmann::json::parse((const char*) m_rx.data(), (const char*) (m_rx.data()+m_rx.size()));
    }

    void                Curl::set_url(const Url&url)
    {
        set_url(to_string(url));
    }
    
    void                Curl::set_url(const UrlView&url)
    {
        set_url(to_string(url));
    }

    void                Curl::set_url(const char*z)
    {
        curl_easy_setopt(m_curl, CURLOPT_URL, z);
    }

    void                Curl::set_url(const std::string&z)
    {
        set_url(z.c_str());
    }

}
